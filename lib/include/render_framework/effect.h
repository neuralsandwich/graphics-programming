#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <GL\glew.h>

namespace render_framework
{
	/*
	Data structure that defines a shader loaded in OpenGL
	*/
	struct shader
	{
		// The filename used to create the shader
		std::string filename;

		// The OpenGL ID of the shader to store
		GLuint id;

		// The type of the shader.
		GLenum type;

		// Creates a shader object.  Sets id initially to 0 (no shader).
		// Default is we read a vertex shader
		shader() : id(0), type(GL_VERTEX_SHADER) { }

		// Destroys the shader object.  If id is not 0, then deletes the
		// shader
		~shader()
		{
			// Check if id is valid, and if so delete
			if (id) glDeleteShader(id);
			// Set id to 0 (no shader)
			id = 0;
		}
	};

	/*
	Data structure that defines an effect built in OpenGL
	*/
	struct effect
	{
		// The OpenGL ID of the effect program
		GLuint program;

		// Vector containing the shaders that make up the effect
		std::vector<std::shared_ptr<shader>> shaders;

		// A map of uniforms mapped to their name in the compiled effect
		std::unordered_map<std::string, GLint> uniforms;

		// A map of uniform blocks mapped to their name in the compiled effect
		std::unordered_map<std::string, GLint> block_uniforms;

		// Creates a new effect.  Ensures program is set to 0 (no program)
		effect() : program(0) { }

		// Destroys an effect.  If program is a valid value (not 0) will delete
		// the program.  Will also clear uniform maps
		~effect()
		{
			if (program)
			{
				if (shaders.size() != 0)
				{
					for (auto iter = shaders.begin(); iter != shaders.end(); ++iter)
					{
						if ((*iter)->id != 0)
						{
							glDetachShader(program, (*iter)->id);
						}
					}
				}
				glDeleteProgram(program);
			}
			shaders.clear();
			uniforms.clear();
			block_uniforms.clear();
			program = 0;
		}

		/*
		Adds a shader to the effect
		*/
		void add_shader(std::shared_ptr<shader> shader)
		{
			shaders.push_back(shader);
		}

		/*
		Adds a shader to the effect
		*/
		void add_shader(const std::string& filename, GLenum type)
		{
			std::shared_ptr<shader> s(new shader);
			s->filename = filename;
			s->type = type;
			shaders.push_back(s);
		}
	};

	/*
	Helper class that will load and build effects
	*/
	class effect_loader
	{
	public:
		// Loads a shader from a given filename
		static std::shared_ptr<shader> load_shader(const std::string& filename, GLenum type);
		// Builds an effect
		static bool build_effect(std::shared_ptr<effect>& value);
	};
}