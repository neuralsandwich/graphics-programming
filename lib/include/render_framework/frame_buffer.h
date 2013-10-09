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
		// The OpenGL ID of the texture generated in the frame buffer
		GLuint tex;
		// The OpenGL ID of the depth buffer in the frame buffer
		GLuint depth;
		// The width of the frame buffer
		unsigned int width;
		// The height of the frame buffer
		unsigned int height;

		// Creates a new frame buffer object.  Sets the necessary OpenGL IDs to
		// zero (no buffer)
		frame_buffer() : buffer(0), tex(0), depth(0) { }

		~frame_buffer()
		{
			// If the buffer is valid (not 0) delete
			if (buffer) glDeleteFramebuffers(1, &buffer);
			// If the texture is valid (not 0) delete
			if (tex) glDeleteTextures(1, &tex);
			// If the depth buffer is valid (not 0) delete
			if (depth) glDeleteRenderbuffers(1, &depth);
			// Set buffers to 0
			buffer = tex = depth = 0;
		}
	};

	/*
	Data structure representing a depth buffer
	*/
	struct depth_buffer
	{
		// The OpenGL buffer ID
		GLuint buffer;
		// The OpenGL texture ID for the texture used to store the depth information
		GLuint depth_texture;
		// The width of the buffer texture
		unsigned int width;
		// The height of the buffer texture
		unsigned int height;

		// Creates a new depth buffer.  Sets OpenGL buffers to 0 (no buffer)
		depth_buffer() : buffer(0), depth_texture(0) { }

		// Destroys the depth buffer.  If buffer and depth texture are valid, 
		// deletes them
		~depth_buffer()
		{
			// If buffer is valid (not 0) delete
			if (buffer) glDeleteFramebuffers(1, &buffer);
			// If texture is valid (not 0) delete
			if (depth_texture) glDeleteTextures(1, & depth_texture);
			// Set OpenGL IDs to 0 (not valid)
			buffer = depth_texture = 0;
		}
	};

	/*
	Data structure representing a shadow map
	*/
	struct shadow_map
	{
		// The direction of the light used in the shadow map development
		glm::vec3 light_direction;
		// The depth buffer storing the depth information
		std::shared_ptr<depth_buffer> buffer;

		// Creates a new shadow map
		shadow_map() : light_direction(-1.0f, 0.0f, 0.0f), buffer(nullptr) { }

		// Destroys the shadow map
		~shadow_map()
		{
			// Reference counting will take care of deletion
		}
	};
}