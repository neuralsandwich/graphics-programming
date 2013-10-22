#include "material.h"
#include "effect.h"
#include "renderer.h"
#include "light.h"
#include "util.h"

namespace render_framework
{
    bool effect_values::bind()
    {
        // Now attempt to bind all the uniform values.
		for (auto iter = value_map.begin(); iter != value_map.end(); ++iter)
		{
			switch (iter->second.first)
			{
			case INT:
				{
					int value = boost::get<int>(iter->second.second);
					if (!renderer::get_instance().set_uniform(iter->first, value))
						return false;
				}
				break;

			case DOUBLE:
				{
					double value = boost::get<double>(iter->second.second);
					if (!renderer::get_instance().set_uniform(iter->first, value))
						return false;
				}
				break;

			case FLOAT:
				{
					float value = boost::get<float>(iter->second.second);
					if (!renderer::get_instance().set_uniform(iter->first, value))
						return false;
				}
				break;

			case UNSIGNED_INT:
				{
					float value = boost::get<unsigned int>(iter->second.second);
					if (!renderer::get_instance().set_uniform(iter->first, value))
						return false;
				}
				break;

			case VEC2:
				{
					glm::vec2 value = boost::get<glm::vec2>(iter->second.second);
					if (!renderer::get_instance().set_uniform(iter->first, value))
						return false;
				}
				break;

			case VEC3:
				{
					glm::vec3 value = boost::get<glm::vec3>(iter->second.second);
					if (!renderer::get_instance().set_uniform(iter->first, value))
						return false;
				}
				break;

			case VEC4:
				{
					glm::vec4 value = boost::get<glm::vec4>(iter->second.second);
					if (!renderer::get_instance().set_uniform(iter->first, value))
						return false;
				}
				break;

			case MAT2:
				{
					glm::mat2 value = boost::get<glm::mat2>(iter->second.second);
					if (!renderer::get_instance().set_uniform(iter->first, value))
						return false;
				}
				break;

			case MAT3:
				{
					glm::mat3 value = boost::get<glm::mat3>(iter->second.second);
					if (!renderer::get_instance().set_uniform(iter->first, value))
						return false;
				}
				break;

			case MAT4:
				{
					glm::mat4 value = boost::get<glm::mat4>(iter->second.second);
					if (!renderer::get_instance().set_uniform(iter->first, value))
						return false;
				}
				break;

			case DIR_LIGHT:
				{
					std::shared_ptr<directional_light> value = boost::get<std::shared_ptr<directional_light>>(iter->second.second);
					// Check if we have a buffer
					if (value->buffer)
					{
						if (!renderer::get_instance().set_uniform_block(iter->first, value->buffer, sizeof(directional_light_data)))
							return false;
					}
					else if (!renderer::get_instance().set_uniform(iter->first, *value))
						return false;
				}
				break;

			case POINT_LIGHT:
				{
					std::shared_ptr<point_light> value = boost::get<std::shared_ptr<point_light>>(iter->second.second);
					if (!renderer::get_instance().set_uniform_block(iter->first, value->buffer, sizeof(point_light)))
						return false;
				}
				break;

			case SPOT_LIGHT:
				{
					std::shared_ptr<spot_light> value = boost::get<std::shared_ptr<spot_light>>(iter->second.second);
					if (!renderer::get_instance().set_uniform_block(iter->first, value->buffer, sizeof(spot_light)))
						return false;
				}
				break;
			}
		}

		// Now do the same for the textures
		// Index of current texture
		int index = 0;
		for (auto iter = texture_map.begin(); iter != texture_map.end(); ++iter)
		{
			if (!renderer::get_instance().bind_texture(iter->second, index))
				return false;
			if (!renderer::get_instance().set_uniform(iter->first, index))
				return false;
			++index;
		}
        for (auto& e : cubemap_map)
        {
            if (!renderer::get_instance().bind_texture(e.second, index))
                return false;
            if (!renderer::get_instance().set_uniform(e.first, index))
                return false;
            ++index;
        }
    }


	//****** TODO - check types of uniform values ******

	template <>
	bool material::set_uniform_value(const std::string& name, const int& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		// Check if effect has uniform of given name
		if (effect->uniforms.find(name) != effect->uniforms.end())
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
	bool material::set_uniform_value(const std::string& name, const double& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (effect->uniforms.find(name) != effect->uniforms.end())
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
	bool material::set_uniform_value(const std::string& name, const float& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (effect->uniforms.find(name) != effect->uniforms.end())
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
	bool material::set_uniform_value(const std::string& name, const unsigned int& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (effect->uniforms.find(name) != effect->uniforms.end())
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
	bool material::set_uniform_value(const std::string& name, const glm::vec2& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (effect->uniforms.find(name) != effect->uniforms.end())
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
	bool material::set_uniform_value(const std::string& name, const glm::vec3& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (effect->uniforms.find(name) != effect->uniforms.end())
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
	bool material::set_uniform_value(const std::string& name, const glm::vec4& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (effect->uniforms.find(name) != effect->uniforms.end())
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
	bool material::set_uniform_value(const std::string& name, const glm::mat2& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (effect->uniforms.find(name) != effect->uniforms.end())
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
	bool material::set_uniform_value(const std::string& name, const glm::mat3& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (effect->uniforms.find(name) != effect->uniforms.end())
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
	bool material::set_uniform_value(const std::string& name, const glm::mat4& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (effect->uniforms.find(name) != effect->uniforms.end())
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

	template <>
	bool material::set_uniform_value(const std::string& name, const std::shared_ptr<directional_light>& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		uniform_values->value_map[name] = std::make_pair(DIR_LIGHT, value);
		return true;
	}

	template <>
	bool material::set_uniform_value(const std::string& name, const std::shared_ptr<point_light>& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (!value->buffer)
		{
			std::cerr << "Point light " << name << " not built" << std::endl;
			return false;
		}
		// Add uniform to material
		uniform_values->value_map[name] = std::make_pair(POINT_LIGHT, value);
		return true;
	}

	template <>
	bool material::set_uniform_value(const std::string& name, const std::shared_ptr<spot_light>& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (!value->buffer)
		{
			std::cerr << "Spot light " << name << " not built" << std::endl;
			return false;
		}
		// Add uniform to material
		uniform_values->value_map[name] = std::make_pair(SPOT_LIGHT, value);
		return true;
	}

	bool material::set_texture(const std::string& name, std::shared_ptr<texture> value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::make_shared<effect_values>();
		if (effect->uniforms.find(name) != effect->uniforms.end())
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

    bool material::set_texture(const std::string& name, std::shared_ptr<cube_map> value)
    {
        if (uniform_values == nullptr)
            uniform_values = std::make_shared<effect_values>();
        if (effect->uniforms.find(name) != effect->uniforms.end())
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

	bool material::bind()
	{
		// Use the effect
		if (!renderer::get_instance().bind(effect))
			return false;

		// Bind the standard material data to material if valid
		if (buffer)
			renderer::get_instance().set_uniform_block("material", buffer, sizeof(material_data));
		// Otherwise try and set the material values individually
		else
			renderer::get_instance().set_uniform("mat", *this);

		if (uniform_values)
		{
            if (!uniform_values->bind())
                return false;
		}

		// Return true
		return true;
	}

	bool material::build()
	{
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(material_data), &data, GL_STATIC_DRAW);
		return !CHECK_GL_ERROR;
	}
}