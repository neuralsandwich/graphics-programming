#include "material.h"
#include "effect.h"
#include "renderer.h"

namespace render_framework
{

	//****** TODO - check types of uniform values ******

	template <>
	bool material::set_uniform_value(const std::string& name, const int& value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::shared_ptr<effect_values>(new effect_values);
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
			uniform_values = std::shared_ptr<effect_values>(new effect_values);
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
			uniform_values = std::shared_ptr<effect_values>(new effect_values);
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
			uniform_values = std::shared_ptr<effect_values>(new effect_values);
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
			uniform_values = std::shared_ptr<effect_values>(new effect_values);
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
			uniform_values = std::shared_ptr<effect_values>(new effect_values);
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
			uniform_values = std::shared_ptr<effect_values>(new effect_values);
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
			uniform_values = std::shared_ptr<effect_values>(new effect_values);
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
			uniform_values = std::shared_ptr<effect_values>(new effect_values);
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
			uniform_values = std::shared_ptr<effect_values>(new effect_values);
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

	bool material::set_texture(const std::string& name, std::shared_ptr<texture> value)
	{
		if (uniform_values == nullptr)
			uniform_values = std::shared_ptr<effect_values>(new effect_values);
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

	bool material::bind()
	{
		// Use the effect
		if (!renderer::get_instance().bind(effect))
			return false;

		// Bind the standard material data to material
		renderer::get_instance().set_uniform_block("Material", buffer, sizeof(material_data));

		if (uniform_values)
		{
			// Now attempt to bind all the uniform values.
			for (auto iter = uniform_values->value_map.begin(); iter != uniform_values->value_map.end(); ++iter)
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
				}
			}

			// Now do the same for the textures
			// Index of current texture
			int index = 0;
			for (auto iter = uniform_values->texture_map.begin(); iter != uniform_values->texture_map.end(); ++iter)
			{
				if (!renderer::get_instance().bind_texture(iter->second, index))
					return false;
				if (!renderer::get_instance().set_uniform(iter->first, index))
					return false;
				++index;
			}
		}

		// Return true
		return true;
	}
}