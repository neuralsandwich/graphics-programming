#include "post_process.h"
#include "material.h"
#include "texture.h"
#include "effect.h"
#include "frame_buffer.h"
#include "renderer.h"
#include "light.h"
#include "util.h"

namespace render_framework
{

	//****** TODO - check types of uniform values ******

	template <>
	bool render_pass::set_uniform_value(const std::string& name, const int& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		// Check if effect has uniform of given name
		if (eff->uniforms.find(name) != eff->uniforms.end())
		{
			uniform_values->value_map[name] = std::make_pair(INT, value);
			return true;
		}
		else
		{
			std::cerr << "Uniform " << name << " does not exist" << std::endl;
			return false;
		}
	}

	template <>
	bool render_pass::set_uniform_value(const std::string& name, const double& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (eff->uniforms.find(name) != eff->uniforms.end())
		{
			uniform_values->value_map[name] = std::make_pair(DOUBLE, value);
			return true;
		}
		else
		{
			std::cerr << "Uniform " << name << " does not exist" << std::endl;
			return false;
		}
	}

	template <>
	bool render_pass::set_uniform_value(const std::string& name, const float& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (eff->uniforms.find(name) != eff->uniforms.end())
		{
			uniform_values->value_map[name] = std::make_pair(FLOAT, value);
			return true;
		}
		else
		{
			std::cerr << "Uniform " << name << " does not exist" << std::endl;
			return false;
		}
	}

	template <>
	bool render_pass::set_uniform_value(const std::string& name, const unsigned int& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (eff->uniforms.find(name) != eff->uniforms.end())
		{
			uniform_values->value_map[name] = std::make_pair(UNSIGNED_INT, value);
			return true;
		}
		else
		{
			std::cerr << "Uniform " << name << " does not exist" << std::endl;
			return false;
		}
	}

	template <>
	bool render_pass::set_uniform_value(const std::string& name, const glm::vec2& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (eff->uniforms.find(name) != eff->uniforms.end())
		{
			uniform_values->value_map[name] = std::make_pair(VEC2, value);
			return true;
		}
		else
		{
			std::cerr << "Uniform " << name << " does not exist" << std::endl;
			return false;
		}
	}

	template <>
	bool render_pass::set_uniform_value(const std::string& name, const glm::vec3& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (eff->uniforms.find(name) != eff->uniforms.end())
		{
			uniform_values->value_map[name] = std::make_pair(VEC3, value);
			return true;
		}
		else
		{
			std::cerr << "Uniform " << name << " does not exist" << std::endl;
			return false;
		}
	}

	template <>
	bool render_pass::set_uniform_value(const std::string& name, const glm::vec4& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (eff->uniforms.find(name) != eff->uniforms.end())
		{
			uniform_values->value_map[name] = std::make_pair(VEC4, value);
			return true;
		}
		else
		{
			std::cerr << "Uniform " << name << " does not exist" << std::endl;
			return false;
		}
	}

	template <>
	bool render_pass::set_uniform_value(const std::string& name, const glm::mat2& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (eff->uniforms.find(name) != eff->uniforms.end())
		{
			uniform_values->value_map[name] = std::make_pair(MAT2, value);
			return true;
		}
		else
		{
			std::cerr << "Uniform " << name << " does not exist" << std::endl;
			return false;
		}
	}

	template <>
	bool render_pass::set_uniform_value(const std::string& name, const glm::mat3& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (eff->uniforms.find(name) != eff->uniforms.end())
		{
			uniform_values->value_map[name] = std::make_pair(MAT3, value);
			return true;
		}
		else
		{
			std::cerr << "Uniform " << name << " does not exist" << std::endl;
			return false;
		}
	}

	template <>
	bool render_pass::set_uniform_value(const std::string& name, const glm::mat4& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (eff->uniforms.find(name) != eff->uniforms.end())
		{
			uniform_values->value_map[name] = std::make_pair(MAT4, value);
			return true;
		}
		else
		{
			std::cerr << "Uniform " << name << " does not exist" << std::endl;
			return false;
		}
	}

	bool render_pass::set_texture(const std::string& name, std::shared_ptr<texture> value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (eff->uniforms.find(name) != eff->uniforms.end())
		{
			uniform_values->texture_map[name] = value;
			return true;
		}
		else
		{
			std::cerr << "Uniform " << name << " does not exist" << std::endl;
			return false;
		}
	}

    bool render_pass::set_texture(const std::string& name, std::shared_ptr<cube_map> value)
    {
        if (uniform_values == nullptr)
            uniform_values = std::make_shared<effect_values>();
        if (eff->uniforms.find(name) != eff->uniforms.end())
        {
            uniform_values->cubemap_map[name] = value;
            return true;
        }
        else
        {
            std::cerr << "Uniform " << name << " does not exist" << std::endl;
            return false;
        }
    }
}