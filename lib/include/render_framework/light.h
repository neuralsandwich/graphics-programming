#pragma once

#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <GL\glew.h>

namespace render_framework
{
	/*
	Structure representing data necessary to define a directional light
	*/
	struct directional_light_data
	{
		// Ambient intensity of main scene light
		glm::vec4 ambient_intensity;
		// Colour of main scene light
		glm::vec4 colour;
		// Direction of main scene light
		glm::vec3 direction;
		// Padding to make data structure size multiple of sizeof vec4
		float _padding;

		// Creates a new directional light.  Default values assigned to 
		// attributes to provide a grey coloured light.
		directional_light_data()
			: ambient_intensity(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)),
			  colour(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f)),
			  direction(glm::vec3(1.0f, 0.0f, 0.0f))
		{
		}
	};
	
	/*
	Structure representing a directional light
	*/
	struct directional_light
	{
		// OpenGL buffer ID for directional light if relevant
		GLuint buffer;

		// Data representing the directional light
		directional_light_data data;

		// Creates a new directional light
		directional_light() : buffer(0) { }

		// Destroys directional light.  If buffer is valid (not 0) will delete
		// the buffer
		~directional_light()
		{
			// If buffer is valid delete
			if (buffer) glDeleteBuffers(1, &buffer);
			// Set buffer to 0
			buffer = 0;
		}

		void rotate(const glm::vec3& rotation);

		void rotate(const glm::quat& rotation);

		void set_ambient_intensity(const glm::vec4& ambient);

		void set_colour(const glm::vec4& colour);
	};
	
	/*
	Structure representing data necessary to define a point light
	*/
	struct point_light_data
	{
		// Colour of the point light
		glm::vec4 colour;
		// Position of the point light
		glm::vec4 position;
		// Attenuation values.  Only x, y and z are used.  These represent the
		// constant, linear and quadratic values of the attentuation factor
		// respectively
		glm::vec4 attenuation;

		// Creates a point light data.  Default values set create a light grey
		// (almost white) light, with a radius of 10.
		point_light_data()
			: colour(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f)),
			  position(glm::vec4(0.0f, 0.0f, -10.0f, 1.0f)),
			  attenuation(glm::vec4(1.0f, 2.0f / 10.0f, 1.0f / (10.0f * 10.0f), 0.0f))
		{
		}
	};

	/*
	Structure representing a point light
	*/
	struct point_light
	{
		// OpenGL buffer ID for the point light data
		GLuint buffer;

		// Actual point light data
		point_light_data data;

		// Creates a point light.  Sets buffer to 0 (no buffer)
		point_light() : buffer(0) { }

		// Deletes point light.  Deletes buffer if valid
		~point_light()
		{
			// If buffer is valid, delete.
			if (buffer) glDeleteBuffers(1, &buffer);
			// Set buffer to 0 (no buffer)
			buffer = 0;
		}

		void translate(const glm::vec3& translation);

		void set_range(float range);

		void set_colour(const glm::vec4& colour);
	};

	/*
	Structure representing data necessary to define a spot light
	*/
	struct spot_light_data
	{
		// Colour of the spot light
		glm::vec4 colour;
		// Position of the spot light.  4D vector for memory alignment.
		// Only x, y, z used
		glm::vec4 position;
		// Direction that the spot light faces.  4D vector for memory alignment.
		// Only x, y, z used
		glm::vec4 direction;
		// Attenuation values.  Only x, y and z are used.  These represent the
		// constant, linear and quadratic values of the attentuation factor
		// respectively
		glm::vec4 attenuation;
		// The power of the spot light
		float power;
		// Padding to align size of data structure to multiple of vec4 size
		float _padding[3];

		/*
		Creates new spot light data.  Initialises colour to be light grey,
		postion to be -10 down the Z axis, and the direction to face up the 
		Z axis.  Range of spot light is 10 units
		*/
		spot_light_data()
			: colour(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f)),
			  position(glm::vec4(0.0f, 0.0f, -10.0f, 1.0f)),
			  direction(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f)),
			  attenuation(glm::vec4(1.0f, 2.0f / 10.0f, 1.0f / (10.0f * 10.0f), 0.0f))
		{
		}
	};

	/*
	Structure representing a spot light
	*/
	struct spot_light
	{
		// OpenGL buffer ID for stored spot light data
		GLuint buffer;
		spot_light_data data;

		spot_light() : buffer(0) { }

		~spot_light()
		{
			if (buffer) glDeleteBuffers(1, &buffer);
			buffer = 0;
		}

		void translate(const glm::vec3& translation);

		void rotate(const glm::vec3& rotation);

		void rotate(const glm::quat& rotation);

		void set_colour(const glm::vec4& colour);

		void set_range(float range);

		void set_power(float power);
	};

	/*
	Structure representing data necessary to define a set of dynamic lights
	*/
	struct dynamic_lights_data
	{
		std::vector<point_light_data> point_lights;
		std::vector<spot_light_data> spot_lights;
	};

	/*
	Structure representing a set of dynamic lights
	*/
	struct dynamic_lights
	{
		GLuint buffer;
		dynamic_lights_data data;

		dynamic_lights() : buffer(0) { }

		~dynamic_lights()
		{
			if (buffer) glDeleteBuffers(1, &buffer);
			buffer = 0;
		}

		void translate_point(int index, const glm::vec3& translation);

		void set_range_point(int index, float range);

		void set_colour_point(int index, const glm::vec4& colour);

		void translate_spot(int index, const glm::vec3& translation);

		void rotate_spot(int index, const glm::vec3& rotation);

		void rotate_spot(int index, const glm::quat& rotation);

		void set_colour_spot(int index, const glm::vec4& colour);

		void set_range_spot(int index, float range);

		void set_power_spot(int index, float power);
	};
}