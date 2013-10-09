#include "texture.h"
#include "util.h"

#include <FreeImage.h>
#include <memory>
#include <glm\gtc\type_ptr.hpp>

#pragma comment(lib, "FreeImage")

namespace render_framework
{
	std::shared_ptr<texture> texture_loader::load(const std::string& name, bool mipmaps, bool anisotropic)
	{
		const char* char_name = name.c_str();
		FREE_IMAGE_FORMAT format = FreeImage_GetFileType(char_name);
		FIBITMAP* image = FreeImage_Load(format, char_name, FREEIMAGE_COLORORDER_RGB);
		FIBITMAP* temp = image;
		image = FreeImage_ConvertTo32Bits(image);
		FreeImage_Unload(temp);
		
		int width = FreeImage_GetWidth(image);
		int height = FreeImage_GetHeight(image);

		GLubyte* pixel_data = FreeImage_GetBits(image);
		GLuint id;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		CHECK_GL_ERROR;
		if (mipmaps)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			CHECK_GL_ERROR;
		}
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			CHECK_GL_ERROR;
        }
		if (anisotropic)
		{
			float max_anisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
			CHECK_GL_ERROR;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pixel_data);
		CHECK_GL_ERROR;
		if (mipmaps)
			glGenerateMipmap(GL_TEXTURE_2D);

		auto tex = std::make_shared<texture>();
		tex->height = height;
		tex->width = width;
		tex->image = id;

		FreeImage_Unload(image);

		CHECK_GL_ERROR;

		return tex;
	}

	std::shared_ptr<cube_map> texture_loader::load(const std::vector<std::string>& names, bool mipmaps, bool anisotropic)
	{
		return nullptr;
	}

	std::shared_ptr<texture> texture_generator::generate()
	{
		return nullptr;
	}

    std::shared_ptr<texture> texture_generator::generate(const std::vector<glm::vec4>& data, unsigned int width, unsigned int height, bool mipmaps, bool anisotropic)
    {
        GLuint id;
        glGenTextures(1, &id);

        if (height == 1)
        {
            glBindTexture(GL_TEXTURE_1D, id);
            if (mipmaps)
            {
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
            else
            {
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            }
            if (anisotropic)
		    {
			    float max_anisotropy;
			    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
			    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
		    }
            glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, width, 0, GL_RGBA, GL_FLOAT, (GLvoid*)&data[0]);
            if (mipmaps)
                glGenerateMipmap(GL_TEXTURE_1D);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, id);
            if (mipmaps)
		    {
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    }
            else
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
		    if (anisotropic)
		    {
			    float max_anisotropy;
			    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
			    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
		    }
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, (GLvoid*)&data[0]);
            if (mipmaps)
			    glGenerateMipmap(GL_TEXTURE_2D);
        }
        

		auto tex = std::make_shared<texture>();
		tex->height = height;
		tex->width = width;
		tex->image = id;
        if (height == 1)
            tex->type = GL_TEXTURE_1D;

        CHECK_GL_ERROR;

        return tex;
    }
}