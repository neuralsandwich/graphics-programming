#include "renderer.h"

#pragma comment(lib, "glfw3dll")
#pragma comment(lib, "GLEW32")
#pragma comment(lib, "OpenGL32")

#include <ctime>
#include <glm\gtc\type_ptr.hpp>

#include "content_manager.h"
#include "effect.h"
#include "frame_buffer.h"
#include "geometry.h"
#include "transform.h"
#include "material.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"
#include "util.h"

namespace render_framework
{
	/*
	Helper function to print OpenGL information
	*/
	void print_GL_info()
	{
		std::clog << "GL Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::clog << "GL Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::clog << "GL Version: " << glGetString(GL_VERSION) << std::endl;
		std::clog << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	}

	/*
	Initialises the renderer
	*/
	bool renderer::initialise()
	{
		// Initialise GLFW
		if (!glfwInit())
		{
			std::cerr << "Error initialising GLFW" << std::endl;
			return false;
		}

		// Get the primary monitor
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		// Now get its current video mode
		const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

		// If we are in debug mode, then set window dimensions to 800 x 600
#if defined(DEBUG) | defined(_DEBUG)
		_window = glfwCreateWindow(800, 600, _caption.c_str(), nullptr, nullptr);
		_width = 800;
		_height = 600;

		// Enable debug
		set_debug();
#else
		// If we are in release mode, then set window dimensions to desktop dimensions
		_window = glfwCreateWindow(vidmode->width, vidmode->height, _caption.c_str(), nullptr, nullptr);
		_width = video_mode.Width;
		_height = video_mode.Height;
#endif
		// Check if window was created
		if (_window == nullptr)
		{
			std::cerr << "Error creating window" << std::endl;
			glfwTerminate();
			return false;
		}

		// Make the window's context current
		glfwMakeContextCurrent(_window);

		// Print OpenGL info
		print_GL_info();

		// Initialise GLEW
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			std::cerr << "Error initialising GLEW: " << glewGetErrorString(error) << std::endl;
			return false;
		}

        // Enable textures
        glEnable(GL_TEXTURE_1D);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_CUBE_MAP);

		// Enable client state to use arrays
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_INDEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		
		if (CHECK_GL_ERROR)
			std::cerr << "Error enabling client states for arrays!" << std::endl;

		// Enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (CHECK_GL_ERROR)
			std::cerr << "Error enabling blending" << std::endl;

		// Enable depth testing
		glEnable(GL_DEPTH_TEST);

		if (CHECK_GL_ERROR)
			std::cerr << "Error enabling depth testing" << std::endl;

		// Enable back face culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		if (CHECK_GL_ERROR)
			std::cerr << "Error enabling back face culling" << std::endl;

		// Enable smoothing
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_MULTISAMPLE);

		if (CHECK_GL_ERROR)
			std::cerr << "Error enabling smoothing / multi-sampling" << std::endl;

		// Enable offsetting - avoids depth conflicts
		glPolygonOffset(1.0f, 1.0f);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glEnable(GL_POLYGON_OFFSET_LINE);
		glEnable(GL_POLYGON_OFFSET_POINT);

		if (CHECK_GL_ERROR)
			std::cerr << "Error enabling polygon offsetting" << std::endl;

		// Enable seamless cube maps
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		if (CHECK_GL_ERROR)
			std::cerr << "Error enabling seamless cube maps" << std::endl;

		// Enable point size manipulation in effects
		glEnable(GL_PROGRAM_POINT_SIZE);

		if (CHECK_GL_ERROR)
			std::cerr << "Error enabling point sizes in shaders" << std::endl;

		// Set running to true
		_running = true;

		// Now create basic content
		// Screen render target
		auto fb = std::make_shared<frame_buffer>();
		content_manager::get_instance().add("SCREEN", fb);

		return true;
	}

	/*
	Shuts down the renderer
	*/
	void renderer::shutdown()
	{
		// Set running to false
		_running = false;

		// Terminate GLFW
		glfwTerminate();
	}

	/*
	Clears the screen
	*/
	void renderer::clear()
	{
		// Check that we are running
		if (!_running)
			return;

		// Clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	/*
	Initiates a render.
	*/
	bool renderer::begin_render()
	{
		// If not running return false
		if (!_running)
			return false;

		// Check if escape is pressed or window closed.  If so, set running to false and return
		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) || glfwWindowShouldClose(_window))
		{
			_running = false;
			return false;
		}

		// Clear the screen
		clear();

		return true;
	}

	/*
	Ends a render.
	*/
	bool renderer::end_render()
	{
		// If not running, return false
		if (!_running)
			return false;

		// Swap the buffers
		swap_buffers();

		// Poll events
		glfwPollEvents();

		return true;
	}

	/*
	Swaps the front and back buffer, displaying the render
	*/
	void renderer::swap_buffers()
	{
		// If not running, return false
		if (!_running)
			return;

		// Swap the buffers
		glfwSwapBuffers(_window);
	}

	/*
    Binds an effect to the renderer
	*/
	template <>
	bool renderer::bind(std::shared_ptr<effect> value)
	{
        // Set the effect on the rendere
		_effect = value;
        // Use the program
		glUseProgram(value->program);
        // Return error check
		return (!CHECK_GL_ERROR);
	}

    /*
    Binds a framebuffer for use on the renderer
    */
	template <>
	bool renderer::bind(std::shared_ptr<frame_buffer> value)
	{
        // Bind the framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, value->buffer);
        // Return error check
		return (!CHECK_GL_ERROR);
	}

    /*
    Binds a depth buffer (framebuffer) for use on the renderer
    */
	template <>
	bool renderer::bind(std::shared_ptr<depth_buffer> value)
	{
        // Bind the framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, value->buffer);
        // Return error check
		return (!CHECK_GL_ERROR);
	}

    /*
    Binds a shadow map for use on the renderer
    */
	template <>
	bool renderer::bind(std::shared_ptr<shadow_map> value)
	{
        // Simply bind the depth buffer.  Return result of this operation
        return bind(value->buffer);
	}

	template <>
	bool renderer::bind(std::shared_ptr<post_process> value)
	{
		return false;
	}

    /*
    Binds a texture for us in an effect
    */
	template <>
	bool renderer::bind_texture(std::shared_ptr<texture> value, unsigned int index)
	{
        // Set the active texture index
		glActiveTexture(GL_TEXTURE0 + index);
        // Bind the type of texture
		glBindTexture(value->type, value->image);
        // Return error check
		return (!CHECK_GL_ERROR);
	}

    /*
    Binds a cube map texture in an effect
    */
	template <>
	bool renderer::bind_texture(std::shared_ptr<cube_map> value, unsigned int index)
	{
        // Set the active texture index
		glActiveTexture(GL_TEXTURE0 + index);
        // Bind the type of texture
		glBindTexture(GL_TEXTURE_CUBE_MAP, value->image);
        // Return error check
        return (!CHECK_GL_ERROR);
	}

    /*
    Sets an int uniform value on the currently bound effect
    */
	template <>
	bool renderer::set_uniform(const std::string& name, const int& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
        // Try and find the uniform on the effect
		auto found = _effect->uniforms.find(name);
		if (found == _effect->uniforms.end())
		{
            // Uniform of given name does not exist in bound effect.  Display error
			std::cerr << "Uniform " << name << " does not exist in current effect" << std::endl;
            // Return false
			return false;
		}
		else
		{
            // Uniform of name does exist.  Set value
			glUniform1i(found->second, value);
            // Return error check
			return (!CHECK_GL_ERROR);
		}
	}
	
	template <>
	bool renderer::set_uniform(const std::string& name, const double& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
        // Try and find the uniform on the effect
		auto found = _effect->uniforms.find(name);
		if (found == _effect->uniforms.end())
		{
            // Uniform of given name does not exist in bound effect.  Display error
			std::cerr << "Uniform " << name << " does not exist in current effect" << std::endl;
            // Return false
			return false;
		}
		else
		{
            // Uniform of name does exist.  Set value
			glUniform1d(found->second, value);
            // Return error check
			return (!CHECK_GL_ERROR);
		}
	}

	template <>
	bool renderer::set_uniform(const std::string& name, const float& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
        // Try and find the uniform on the effect
		auto found = _effect->uniforms.find(name);
		if (found == _effect->uniforms.end())
		{
            // Uniform of given name does not exist in bound effect.  Display error
			std::cerr << "Uniform " << name << " does not exist in current effect" << std::endl;
            // Return false
			return false;
		}
		else
		{
            // Uniform of name does exist.  Set value
			glUniform1f(found->second, value);
            // Return error check
			return (!CHECK_GL_ERROR);
		}
	}

	template <>
	bool renderer::set_uniform(const std::string& name, const unsigned int& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
        // Try and find the uniform on the effect
		auto found = _effect->uniforms.find(name);
		if (found == _effect->uniforms.end())
		{
            // Uniform of given name does not exist in bound effect.  Display error
			std::cerr << "Uniform " << name << " does not exist in current effect" << std::endl;
            // Return false
			return false;
		}
		else
		{
            // Uniform of name does exist.  Set value
			glUniform1ui(found->second, value);
            // Return error check
			return (!CHECK_GL_ERROR);
		}
	}

	template <>
	bool renderer::set_uniform(const std::string& name, const glm::vec2& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
        // Try and find the uniform on the effect
		auto found = _effect->uniforms.find(name);
		if (found == _effect->uniforms.end())
		{
            // Uniform of given name does not exist in bound effect.  Display error
			std::cerr << "Uniform " << name << " does not exist in current effect" << std::endl;
            // Return false
			return false;
		}
		else
		{
            // Uniform of name does exist.  Set value
			glUniform2fv(found->second, 1, glm::value_ptr(value));
            // Return error check
			return (!CHECK_GL_ERROR);
		}
	}

	template <>
	bool renderer::set_uniform(const std::string& name, const glm::vec3& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
        // Try and find the uniform on the effect
		auto found = _effect->uniforms.find(name);
		if (found == _effect->uniforms.end())
		{
            // Uniform of given name does not exist in bound effect.  Display error
			std::cerr << "Uniform " << name << " does not exist in current effect" << std::endl;
            // Return false
			return false;
		}
		else
		{
            // Uniform of name does exist.  Set value
			glUniform3fv(found->second, 1, glm::value_ptr(value));
            // Return error check
			return (!CHECK_GL_ERROR);
		}
	}

	template <>
	bool renderer::set_uniform(const std::string& name, const glm::vec4& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
        // Try and find the uniform on the effect
		auto found = _effect->uniforms.find(name);
		if (found == _effect->uniforms.end())
		{
            // Uniform of given name does not exist in bound effect.  Display error
			std::cerr << "Uniform " << name << " does not exist in current effect" << std::endl;
            // Return false
			return false;
		}
		else
		{
            // Uniform of name does exist.  Set value
			glUniform4fv(found->second, 1, glm::value_ptr(value));
            // Return error check
			return (!CHECK_GL_ERROR);
		}
	}

	template <>
	bool renderer::set_uniform(const std::string& name, const glm::mat2& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
        // Try and find the uniform on the effect
		auto found = _effect->uniforms.find(name);
		if (found == _effect->uniforms.end())
		{
            // Uniform of given name does not exist in bound effect.  Display error
			std::cerr << "Uniform " << name << " does not exist in current effect" << std::endl;
            // Return false
			return false;
		}
		else
		{
            // Uniform of name does exist.  Set value
			glUniformMatrix2fv(found->second, 1, GL_FALSE, glm::value_ptr(value));
            // Return error check
			return (!CHECK_GL_ERROR);
		}
	}

	template <>
	bool renderer::set_uniform(const std::string& name, const glm::mat3& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
        // Try and find the uniform on the effect
		auto found = _effect->uniforms.find(name);
		if (found == _effect->uniforms.end())
		{
            // Uniform of given name does not exist in bound effect.  Display error
			std::cerr << "Uniform " << name << " does not exist in current effect" << std::endl;
            // Return false
			return false;
		}
		else
		{
            // Uniform of name does exist.  Set value
			glUniformMatrix3fv(found->second, 1, GL_FALSE, glm::value_ptr(value));
            // Return error check
			return (!CHECK_GL_ERROR);
		}
	}

	template <>
	bool renderer::set_uniform(const std::string& name, const glm::mat4& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
        // Try and find the uniform on the effect
		auto found = _effect->uniforms.find(name);
		if (found == _effect->uniforms.end())
		{
            // Uniform of given name does not exist in bound effect.  Display error
			std::cerr << "Uniform " << name << " does not exist in current effect" << std::endl;
            // Return false
			return false;
		}
		else
		{
            // Uniform of name does exist.  Set value
			glUniformMatrix4fv(found->second, 1, GL_FALSE, glm::value_ptr(value));
            // Return error check
			return (!CHECK_GL_ERROR);
		}
	}

	template <>
	bool renderer::set_uniform(const std::string& name, const directional_light& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
		return false;
	}

	template <>
	bool renderer::set_uniform(const std::string& name, const point_light& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
		return false;
	}

	template <>
	bool renderer::set_uniform(const std::string& name, const spot_light& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
		return false;
	}

	template <>
	bool renderer::set_uniform(const std::string& name, const material& value)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
		return false;
	}

	bool renderer::set_uniform_block(const std::string& name, unsigned int buffer, int size)
	{
        // Check that effect is bound
        if (_effect == nullptr)
        {
            // Display error
            std::cerr << "Cannot set uniform - no effect bound with renderer" << std::endl;
            // Return false
            return false;
        }
		auto found = _effect->block_uniforms.find(name);
		if (found == _effect->block_uniforms.end())
			return false;
		else
		{
			glBindBufferRange(GL_UNIFORM_BUFFER, found->second, buffer, 0, size);
			return true;
		}
	}

	/*
	Helper function to set model-view and projection matrices
	*/
	void set_mvp(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
	{
		// Set the projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(projection));

		// Set the model view matrix
		glm::mat4 modelView = view * model;
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(modelView));
	}

	/*
	Helper function to set model-view and projection matrices on a effect
	*/
	void set_mvp(std::shared_ptr<effect> eff, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
	{
		// Try and set the model matrix
        if (eff->uniforms.find("model") != eff->uniforms.end())
		    renderer::get_instance().set_uniform("model", model);
		// Try and set the view matrix
        if (eff->uniforms.find("view") != eff->uniforms.end())
		    renderer::get_instance().set_uniform("view", view);
		// Try and set the projection matrix
        if (eff->uniforms.find("projection") != eff->uniforms.end())
		    renderer::get_instance().set_uniform("projection", projection);
		// Create model-view matrix and try and set
        if (eff->uniforms.find("MV") != eff->uniforms.end())
        {
		    glm::mat4 modelView = view * model;
		    renderer::get_instance().set_uniform("MV", modelView);
        }
		// Create model-view-projection matrix and try and set
        if (eff->uniforms.find("MVP") != eff->uniforms.end())
        {
		    glm::mat4 modelViewProjection = projection * view * model;
		    renderer::get_instance().set_uniform("MVP", modelViewProjection);
        }
	}

    bool validate_program(std::shared_ptr<effect> value)
    {
        glValidateProgram(value->program);
        GLint status;
        glGetProgramiv(value->program, GL_VALIDATE_STATUS, &status);
        if (!status)
        {
            GLsizei length;
            glGetProgramiv(value->program, GL_INFO_LOG_LENGTH, &length);
            std::unique_ptr<char[]> log(new char[length]);
            glGetProgramInfoLog(value->program, length, &length, log.get());
            std::cerr << "Error running program - could not validate" << std::endl;
            std::cerr << log.get() << std::endl;
            return false;
        }
        return true;
    }

	template <>
	bool renderer::render(std::shared_ptr<geometry> value)
	{
        // Check if running
		if (!_running)
			return false;

		// If an effect is enabled, then set view and projection values
		if (_effect != nullptr)
		{
            // If we have a set camera, use it to get view and projection matrices
			if (_camera != nullptr)
				set_mvp(_effect, glm::mat4(1.0f), _camera->get_view(), _camera->get_projection());
            // Otherwise use the bound view and projection
			else
				set_mvp(_effect, glm::mat4(1.0f), _view, _projection);
            if (!validate_program(_effect))
                return false;
		}
        // Otherwise use deprecated matrix binding
		else
		{
            // If we have a set camera, use it to get view and projection matrices
			if (_camera != nullptr)
				set_mvp(glm::mat4(1.0f), _camera->get_view(), _camera->get_projection());
            // Otherwise use the bound view and projection
			else
				set_mvp(glm::mat4(1.0f), _view, _projection);
		}

		// Now render the geometry
        // Try and bind the vertex array
		glBindVertexArray(value->vertex_array_object);
        // Check if error
		if (CHECK_GL_ERROR)
		{
			std::cerr << "Error trying to bind vertex array for geometry" << std::endl;
			return false;
		}

		// If we have indices, use accordingly.
		if (value->index_buffer)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, value->index_buffer);
			if (CHECK_GL_ERROR)
			{
				std::cerr << "Error trying to bind index buffer for use in geometry render" << std::endl;
				return false;
			}

			glDrawElements(value->geometry_type, value->indices.size(), GL_UNSIGNED_INT, 0);
			if (CHECK_GL_ERROR)
			{
				std::cerr << "Error trying to draw using index buffer using geometry" << std::endl;
				return false;
			}
		}
		else
		{
			glDrawArrays(value->geometry_type, 0, value->positions.size());
			if (CHECK_GL_ERROR)
			{
				std::cerr << "Error trying to draw geometry" << std::endl;
				return false;
			}
		}

		return true;
	}

	template<>
	bool renderer::render(std::shared_ptr<model> value)
	{
		return false;
	}

	template <>
	bool renderer::render(std::shared_ptr<texture> value)
	{
		return false;
	}

	template <>
	bool renderer::render(std::shared_ptr<skybox> value)
	{
		return false;
	}

	template <>
	bool renderer::render(std::shared_ptr<terrain> value)
	{
		return false;
	}

	template <>
	bool renderer::render(std::shared_ptr<mesh> value)
	{
		if (!_running)
			return false;

		// Check if mesh has a material
		if (value->mat)
			// Mesh has a material.  Bind
			value->mat->bind();
		else
			// Mesh doesn't have a material.  Set _effect to nullptr
			_effect = nullptr;

		// If an effect is enabled, then set view and projection values
		if (_effect != nullptr)
		{
			if (_camera)
				set_mvp(_effect, value->trans.get_transform_matrix(), _camera->get_view(), _camera->get_projection());
			else
				set_mvp(_effect, value->trans.get_transform_matrix(), _view, _projection);
			// Set the normal matrix if present
            if (_effect->uniforms.find("normal_matrix") != _effect->uniforms.end())
			    set_uniform("normal_matrix", value->trans.get_normal_matrix());
            if (!validate_program(_effect))
                return false;
		}
		else
		{
			if (_camera)
				set_mvp(value->trans.get_transform_matrix(), _camera->get_view(), _camera->get_projection());
			else
				set_mvp(value->trans.get_transform_matrix(), _view, _projection);
		}

		// Now render the geometry
		glBindVertexArray(value->geom->vertex_array_object);
		if (CHECK_GL_ERROR)
		{
			std::cerr << "Error trying to bind vertex array for mesh" << std::endl;
			return false;
		}

		// If we have indices, use accordingly.
		if (value->geom->index_buffer)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, value->geom->index_buffer);
			if (CHECK_GL_ERROR)
			{
				std::cerr << "Error trying to bind index buffer for use in mesh render" << std::endl;
				return false;
			}

			glDrawElements(value->geom->geometry_type, value->geom->indices.size(), GL_UNSIGNED_INT, 0);
			if (CHECK_GL_ERROR)
			{
				std::cerr << "Error trying to draw using index buffer using mesh" << std::endl;
				return false;
			}
		}
		else
		{
			glDrawArrays(value->geom->geometry_type, 0, value->geom->positions.size());
			if (CHECK_GL_ERROR)
			{
				std::cerr << "Error trying to draw mesh" << std::endl;
				return false;
			}
		}

		return true;
	}

	template <>
	bool renderer::render(std::shared_ptr<frame_buffer> value)
	{
		return false;
	}

	template <>
	bool renderer::render(std::shared_ptr<depth_buffer> value)
	{
		return false;
	}

	template <>
	bool renderer::render(std::shared_ptr<shadow_map> value)
	{
		return false;
	}

	template <>
	bool renderer::render(std::shared_ptr<render_pass> value)
	{
		return false;
	}

	template <>
	bool renderer::render(std::shared_ptr<post_process> value)
	{
		return false;
	}
}