#include "effect.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

namespace render_framework
{
	// Helper function used to read in a file
	bool read_file(const std::string& filename, std::string& content)
	{
		// Create filestream
		std::ifstream file(filename, std::ios_base::in);
		// Check that file exists.  If not, return false
		if (file.bad())
			return false;

		// File is good.  Read contents
		std::stringstream buffer;
		buffer << file.rdbuf();

		// Get contents from the file
		content = buffer.str();

		// Close file and return true
		file.close();
		return true;
	}

	// Loads a shader from a given filename
	std::shared_ptr<shader> effect_loader::load_shader(const std::string& filename, GLenum type)
	{
		// String holding the contents of the shader file
		std::string content;
		// First read in file contents.  Check if file read is OK
		if (!read_file(filename, content))
		{
			// Failed to read file.  Display error
			std::cerr << "Failed to read file " << filename << std::endl;
			return nullptr;
		}
		// Create new shader object
		auto value = std::make_shared<shader>();
		value->type = type;
		// File has been read.  Try and create shader
		value->id = glCreateShader(value->type);
		// File contents a character array
		auto source = content.c_str();
		// Set the source code of the shader
		glShaderSource(value->id, 1, &source, 0);
		// Compile shader
		glCompileShader(value->id);
		CHECK_GL_ERROR;

		// We have tried to compile the shader.  Check if successful
		// Compile status of the shader
		GLint compiled;
		// Get the compile status
		glGetShaderiv(value->id, GL_COMPILE_STATUS, &compiled);
		CHECK_GL_ERROR;
		// Check if compiled
		if (!compiled)
		{
			// Shader not compiled.  Get log and display
			// Length of the shader compile log
			GLsizei length;

			// Get length of log
			glGetShaderiv(value->id, GL_INFO_LOG_LENGTH, &length);
			// Use the length to create log buffer
			// Buffer for the log
			std::unique_ptr<char[]> log(new char[length]);
			// Get the log
			glGetShaderInfoLog(value->id, length, &length, log.get());
			// Display error message
			std::cout << "Could not compile shader " << filename << std::endl;
			std::cout << log.get() << std::endl;
			CHECK_GL_ERROR;
			// Return nullptr
			return nullptr;
		}

		// Shader has been created OK.  Log and return true
		std::clog << "Shader " << filename << " loaded" << std::endl;
		return value;
	}

	// Builds an effect from a list of shaders
	bool effect_loader::build_effect(std::shared_ptr<effect>& value)
	{
		// Create program object
		value->program = glCreateProgram();
		CHECK_GL_ERROR;
		// Check which shaders need to be built
		for (auto iter = value->shaders.begin(); iter != value->shaders.end(); ++iter)
		{
			if (!(*iter)->id)
			{
				auto loaded = load_shader((*iter)->filename, (*iter)->type);
				if (loaded == nullptr)
					return nullptr;
				else
					(*iter) = loaded;
			}
		}

		// Now attach all the shaders involved into the program
		for (auto iter = value->shaders.begin(); iter != value->shaders.end(); ++iter)
			glAttachShader(value->program, (*iter)->id);

		// Attempt to link program
		glLinkProgram(value->program);
		CHECK_GL_ERROR;
		// Check if linked successfully.
		// Link status
		GLint linked;
		glGetProgramiv(value->program, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			// Program did not link.  Get info log and display error
			// Length of info log
			GLsizei length;
			// Get length of log
			glGetProgramiv(value->program, GL_INFO_LOG_LENGTH, &length);
			// Use length to create log buffer
			// Info log
			std::unique_ptr<char[]> log(new char[length]);
			// Get info log
			glGetProgramInfoLog(value->program, length, &length, log.get());
			// Display error
			std::cerr << "Error linking program" << std::endl;
			std::cerr << log.get() << std::endl;
			// Detach shaders
			for (auto iter = value->shaders.begin(); iter != value->shaders.end(); ++iter)
				glDetachShader(value->program, (*iter)->id);
			// Delete program
			glDeleteProgram(value->program);
			CHECK_GL_ERROR;
			// Return false
			return false;
		}

		// Effect built successfully.  Log
		std::clog << "Effect built" << std::endl;

		// Now get the uniforms associated with the program
		// Number of uniforms in the shader
		GLint numUniforms;
		// Maximum uniform name length
		GLint maxLength;
		// Get the maximum uniform name length
		glGetProgramiv(value->program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
		// Get the number of uniforms
		glGetProgramiv(value->program, GL_ACTIVE_UNIFORMS, &numUniforms);
		// Buffer to store names of uniforms
		std::unique_ptr<char> buf(new char[maxLength]);
		CHECK_GL_ERROR;
		// Iterate through all uniforms and add to the uniforms attached to the
		// program
		// Length of the uniform name
		GLsizei size;
		for (int i = 0; i < numUniforms; ++i)
		{
			// Get the name of the uniform
			glGetActiveUniformName(value->program, i, maxLength, &size, buf.get());
			CHECK_GL_ERROR;
			// Convert to string
			std::string name(buf.get());
			// Check if uniform exists in the uniforms already.  Strange glitch?
			if (value->uniforms.size() > 0 && value->uniforms.find(name) != value->uniforms.end())
				break;
			else
			{
				// Get location of the uniform
				// Uniform location
				GLint uniformLocation;
				// Get the uniform location
				uniformLocation = glGetUniformLocation(value->program, name.c_str());
				CHECK_GL_ERROR;
				// Check is valid, and is so add to the uniforms
				if (uniformLocation != -1)
					value->uniforms[name] = uniformLocation;
			}
		}

		// Now do the same for uniform blocks
		// Get the maximum uniform block name length
		glGetProgramiv(value->program, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, &maxLength);
		// Get the number of uniform blocks
		glGetProgramiv(value->program, GL_ACTIVE_UNIFORM_BLOCKS, &numUniforms);
		CHECK_GL_ERROR;
		// Initialise buffer at required length
		buf.reset(new char[maxLength]);
		// Iterate through each block and add to effect data
		for (int i = 0; i < numUniforms; ++i)
		{
			// Get the name of the uniform block
			glGetActiveUniformBlockName(value->program, i, maxLength, &size, buf.get());
			CHECK_GL_ERROR;
			// Convert to string
			std::string name(buf.get());
			// Check if uniform block exists in uniforms blocks already. Glitch?
			if (value->block_uniforms.size() > 0 && value->block_uniforms.find(name) != value->block_uniforms.end())
				break;
			else
			{
				// Get block index
				// Block index
				GLuint blockIndex = glGetUniformBlockIndex(value->program, name.c_str());
				// Bind the block to current index (i)
				glUniformBlockBinding(value->program, blockIndex, i);
				// Store the name mapped to this index
				value->block_uniforms[name] = i;
				CHECK_GL_ERROR;
			}
		}

		// All uniforms added to effect and effect built.  Return true
		return true;
	}
}