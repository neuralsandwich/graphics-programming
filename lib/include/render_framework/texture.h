#pragma once

#include <string>
#include <vector>
#include <memory>
#include <GL\glew.h>
#include <glm\glm.hpp>

namespace render_framework
{
	/*
	Structure representing a texture
	*/
	struct texture
	{
		// The texture ID as stored by OpenGL
		GLuint image;
		// The width of the texture
		GLuint width;
		// The height of the texture
		GLuint height;
		// The type of the texture
		GLenum type;

		// Creates a new texture
		texture() : image(0), width(0), height(0), type(GL_TEXTURE_2D) { }

		// Destroys the texture.  Will delete from OpenGL if valid.
		~texture()
		{
			// Check if image is valid, and if so delete
			if (image != 0) glDeleteTextures(1, &image);
			// Set image value to 0 (no image)
			image = 0;
		}
	};

	/*
	Structure representing a cube map
	*/
	struct cube_map
	{
		// The texture ID as stored by OpenGL
		GLuint image;
		// The filenames to be used to generate the cubemap
		std::vector<std::string> filenames;

		// Creates a new cube map
		cube_map() : image(0) { }

		// Destroys the cube map.  Will delete from OpenGL if valid
		~cube_map()
		{
			// Check if image is valid, and if so delete
			if (image) glDeleteTextures(1, &image);
			// Set image value to 0 (no image)
			image = 0;
		}
	};

	/*
	Helper class used to load textures
	*/
	class texture_loader
	{
	public:
		// Loads a texture using the given file name
		static std::shared_ptr<texture> load(const std::string& filename, bool mipmaps = true, bool anisotropic = true);
		// Loads a cube maps using the given array of file names
		static std::shared_ptr<cube_map> load(const std::vector<std::string>& names, bool mipmaps = true, bool anisotropic = true);
	};

	/*
	Helper class used to procedurally generate textures
	*/
	class texture_generator
	{
	public:
		// Generates a texture using a noise function
		static std::shared_ptr<texture> generate(/* TODO noise - enum to hide libnoise */);
		// Generates a texture using a multi-dimensional arrray of colour data
		static std::shared_ptr<texture> generate(const std::vector<glm::vec4>& data, unsigned int width, unsigned int height, bool mipmaps = true, bool anisotropic = true);
	};
}