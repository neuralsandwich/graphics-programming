#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <boost\variant.hpp>
#include "light.h"

namespace render_framework
{
	enum UNIFORM_TYPE
	{
		INT,
		DOUBLE,
		FLOAT,
		UNSIGNED_INT,
		VEC2,
		VEC3,
		VEC4,
		MAT2,
		MAT3,
		MAT4,
		DIR_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT
	};

	// Forward declaration of effect struct.  Used as part of a material
	struct effect;

	// Forward declaration of texture struct.  Used as part of a material
	struct texture;

    // Forward declaration of cubemap struct.  Used as part of a material
    struct cube_map;

	/*
	Structure representing data required for a material
	*/
	struct material_data
	{
		// The emissive component of the material colour
		glm::vec4 emissive;
		// The diffuse reflection component of the material colour
		glm::vec4 diffuse_reflection;
		// The specular reflection component of the material colour
		glm::vec4 specular_reflection;
		// Shininess of the material
		float shininess;
		// Some padding.  Will make the material data size divisible by the 
		// sizeof a vec4
		float _padding[3];

		/*
		Creates a new piece of material data.  Sets some basic default values 
		for the material.  The values will provide a light grey colour, with
		some shininess.
		*/
		material_data()
			: emissive(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
			  diffuse_reflection(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
			  specular_reflection(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
			  shininess(100.0f)
		{
		}
	};

	// Structure containing set uniform values for an effect
	struct effect_values
	{
		std::unordered_map<std::string, 
			std::pair<UNIFORM_TYPE, boost::variant<int, 
												   double,
												   float,
												   unsigned int,
												   glm::vec2,
												   glm::vec3,
												   glm::vec4,
												   glm::mat2,
												   glm::mat3,
												   glm::mat4,
												   std::shared_ptr<directional_light>,
												   std::shared_ptr<point_light>,
												   std::shared_ptr<spot_light>>>> value_map;
		std::unordered_map<std::string, std::shared_ptr<texture>> texture_map;
        std::unordered_map<std::string, std::shared_ptr<cube_map>> cubemap_map;

		~effect_values()
		{
			value_map.clear();
			texture_map.clear();
		}

        bool bind();
	};

	// Forward declaration of texture
	struct texture;

	/*
	Structure representing a material.  This includes the material data and the
	buffer on the GPU (if relevant)
	*/
	struct material
	{
		// The ID of the buffer as stored in OpenGL
		GLuint buffer;
		// Data stored in the buffer
		material_data data;
		// Effect attached to the material
		std::shared_ptr<effect> effect;
		// Uniform values to set in the effect
		std::shared_ptr<effect_values> uniform_values;

		// Creates a material object.  Ensures buffer is set to 0 (no buffer)
		material() : buffer(0), effect(nullptr), uniform_values(nullptr) { }

		// Deletes a material.  Will delete the buffer if it is valid (not 0)
		~material()
		{
			// Check if buffer is valid (not 0), and if so delete
			if (buffer) glDeleteBuffers(1, &buffer);
			// Set buffer to 0 (no buffer)
			buffer = 0;
		}

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

		/*
		Binds the material for use
		*/
		bool bind();

		/*
		Builds the material initialising the uniform buffer
		*/
		bool build();
	};

	/*
	Default method for setting a uniform value.  This is called when an unknown
	/ incorrect type has been used.  Will display an error message and return
	false
	*/
	template <typename T>
	bool material::set_uniform_value(const std::string& name, const T& value)
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
	bool material::set_uniform_value(const std::string& name, const int& value);

	/*
	Provides a double value for the uniform of the given name
	*/
	extern template
	bool material::set_uniform_value(const std::string& name, const double& value);

	/*
	Provides a float value for the uniform of the given name
	*/
	extern template
	bool material::set_uniform_value(const std::string& name, const float& value);

	/*
	Provides an unsigned int value for the uniform of the given name
	*/
	extern template
	bool material::set_uniform_value(const std::string& name, const unsigned int& value);

	/*
	Provides a vec2 value for the uniform of the given name
	*/
	extern template
	bool material::set_uniform_value(const std::string& name, const glm::vec2& value);

	/*
	Provides a vec3 value for the uniform of the given name
	*/
	extern template
	bool material::set_uniform_value(const std::string& name, const glm::vec3& value);

	/*
	Provides a vec4 value for the uniform of the given name
	*/
	extern template
	bool material::set_uniform_value(const std::string& name, const glm::vec4& value);

	/*
	Provides a mat2 value for the uniform of the given name
	*/
	extern template
	bool material::set_uniform_value(const std::string& name, const glm::mat2& value);

	/*
	Provides a mat3 value for the uniform of the given name
	*/
	extern template
	bool material::set_uniform_value(const std::string& name, const glm::mat3& value);

	/*
	Provides a mat4 value for the uniform of the given name
	*/
	extern template
	bool material::set_uniform_value(const std::string& name, const glm::mat4& value);

	/*
	Provides a directional light value for the uniform of the given name
	*/
	extern template
	bool material::set_uniform_value(const std::string& name, const std::shared_ptr<directional_light>& value);

	/*
	Provides a point light value for the uniform of the given name
	*/
	extern template
	bool material::set_uniform_value(const std::string& name, const std::shared_ptr<point_light>& value);

	/*
	Provides a spot light value for the uniform of the given name
	*/
	extern template
	bool material::set_uniform_value(const std::string& name, const std::shared_ptr<spot_light>& value);
}