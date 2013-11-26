#pragma once

#include <vector>
#include <memory>
#include <glm\glm.hpp>

namespace render_framework
{
	// Forward declarations
	struct frame_buffer;
	struct geometry;
	struct effect;
	struct effect_values;
	struct texture;
	struct cube_map;

	/*
	Structure representing a render pass in the render framework
	*/
	struct render_pass
	{
		// Frame buffer to store render pass information in
		std::shared_ptr<frame_buffer> buffer;
		// Effect used in the render pass
		std::shared_ptr<effect> eff;
		// Effect values for the render pass
		std::shared_ptr<effect_values> uniform_values;

		render_pass() : buffer(nullptr), eff(nullptr), uniform_values(nullptr) { }

		/*
		Provides a method to define a uniform value for the effect
		*/
		template <typename T>
		bool set_uniform_value(const std::string& name, const T& value);

		/*
		Sets a texture to be used by the effect
		*/
		bool set_texture(const std::string& name, std::shared_ptr<texture> value);

		/*
		Sets a cubemap texture to be used by the effect
		*/
		bool set_texture(const std::string& name, std::shared_ptr<cube_map> value);
	};

	/*
	Structure representing a post process in the render framework
	*/
	struct post_process
	{
		// Vector of render passes used in the post process
		std::vector<std::shared_ptr<render_pass>> passes;
	};

	/*
	Default method for setting a uniform value.  This is called when an unknown
	/ incorrect type has been used.  Will display an error message and return
	false
	*/
	template <typename T>
	bool render_pass::set_uniform_value(const std::string& name, const T& value)
	{
		// Display error
		std::cerr << "Error trying to set uniform of unknown type" << std::endl;
		std::cerr << "Type: " << typeid(T).name() << std::endl;
		// Return false
		return false;
	}

	/*
	Provides an int value for the uniform of the given name
	*/
	extern template
		bool render_pass::set_uniform_value(const std::string& name, const int& value);

	/*
	Provides a double value for the uniform of the given name
	*/
	extern template
		bool render_pass::set_uniform_value(const std::string& name, const double& value);

	/*
	Provides a float value for the uniform of the given name
	*/
	extern template
		bool render_pass::set_uniform_value(const std::string& name, const float& value);

	/*
	Provides an unsigned int value for the uniform of the given name
	*/
	extern template
		bool render_pass::set_uniform_value(const std::string& name, const unsigned int& value);

	/*
	Provides a vec2 value for the uniform of the given name
	*/
	extern template
		bool render_pass::set_uniform_value(const std::string& name, const glm::vec2& value);

	/*
	Provides a vec3 value for the uniform of the given name
	*/
	extern template
		bool render_pass::set_uniform_value(const std::string& name, const glm::vec3& value);

	/*
	Provides a vec4 value for the uniform of the given name
	*/
	extern template
		bool render_pass::set_uniform_value(const std::string& name, const glm::vec4& value);

	/*
	Provides a mat2 value for the uniform of the given name
	*/
	extern template
		bool render_pass::set_uniform_value(const std::string& name, const glm::mat2& value);

	/*
	Provides a mat3 value for the uniform of the given name
	*/
	extern template
		bool render_pass::set_uniform_value(const std::string& name, const glm::mat3& value);

	/*
	Provides a mat4 value for the uniform of the given name
	*/
	extern template
		bool render_pass::set_uniform_value(const std::string& name, const glm::mat4& value);
}