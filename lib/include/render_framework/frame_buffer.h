#pragma once

#include <gl\glew.h>
#include <glm\glm.hpp>

namespace render_framework
{
	/*
	Data structure representing a frame buffer
	*/
	struct frame_buffer
	{
		// The buffer ID used in OpenGL
		GLuint buffer;
		// Texture generated in the frame buffer
		std::shared_ptr<texture> tex;
		// The OpenGL ID of the depth buffer in the frame buffer
		std::shared_ptr<texture> depth;
		// The width of the frame buffer
		unsigned int width;
		// The height of the frame buffer
		unsigned int height;

		// Creates a new frame buffer object.  Sets the necessary OpenGL IDs to
		// zero (no buffer)
		frame_buffer() : buffer(0), depth(0) { tex = std::make_shared<texture>(); }

		~frame_buffer()
		{
			// If the buffer is valid (not 0) delete
			if (buffer) glDeleteFramebuffers(1, &buffer);
			// Set buffer to 0
			buffer = 0;
		}
	};

	/*
	Data structure representing a depth buffer
	*/
	struct depth_buffer
	{
		// The OpenGL buffer ID
		GLuint buffer;
		// Texture used to store the depth information
		std::shared_ptr<texture> depth_texture;
		// The width of the buffer texture
		unsigned int width;
		// The height of the buffer texture
		unsigned int height;

		// Creates a new depth buffer.  Sets OpenGL buffers to 0 (no buffer)
		depth_buffer() : buffer(0) { depth_texture = std::make_shared<texture>(); }

		// Destroys the depth buffer.  If buffer and depth texture are valid, 
		// deletes them
		~depth_buffer()
		{
			// If buffer is valid (not 0) delete
			if (buffer) glDeleteFramebuffers(1, &buffer);
			// Set OpenGL IDs to 0 (not valid)
			buffer = 0;
		}
	};

	/*
	Data structure representing a shadow map
	*/
	struct shadow_map
	{
        // Matrix used a bias when calculating shadow matrix
		static glm::mat4 bias;
		// The position of the light used in the shadow map development
		glm::vec3 light_position;
		// The direction of the light used in the shadow map development
		glm::vec3 light_direction;
		// The depth buffer storing the depth information
		std::shared_ptr<depth_buffer> buffer;
		// Projection matrix for this shadow map
		glm::mat4 projection_matrix;
		// View matrix for this shadow map
		glm::mat4 view_matrix;

		// Creates a new shadow map
		shadow_map() : light_position(0.0f, 0.0f, 0.0f), light_direction(-1.0f, 0.0f, 0.0f), buffer(nullptr) { }

		// Destroys the shadow map
		~shadow_map()
		{
			// Reference counting will take care of deletion
		}
	};
}