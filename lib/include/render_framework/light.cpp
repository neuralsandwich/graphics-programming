#include "light.h"
#include "util.h"

namespace render_framework
{
	void directional_light::rotate(const glm::vec3& rotation)
	{
		// Convert to a quaternion
		glm::quat q(rotation);
		// Use quaternion based rotate
		rotate(q);
	}

	void directional_light::rotate(const glm::quat& rotation)
	{
		// Calculate the new orientation
		auto rot = glm::mat3_cast(rotation);
		data.direction = rot * data.direction;
		// Check if buffer
		if (!buffer)
			return;
		// Change buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), sizeof(glm::vec3), &data.direction);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void directional_light::set_ambient_intensity(const glm::vec4& ambient)
	{
		// Set the ambient intensity
		data.ambient_intensity = ambient;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), &data.ambient_intensity);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void directional_light::set_colour(const glm::vec4& colour)
	{
		// Set the colour of the light
		data.colour = colour;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec4), &data.colour);
		// Display any errors
		CHECK_GL_ERROR;
	}

	bool directional_light::build()
	{
		// Generate the buffer
		glGenBuffers(1, &buffer);
		// Bind
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		// Set the buffer data
		glBufferData(GL_UNIFORM_BUFFER, sizeof(directional_light_data), &data, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		return !CHECK_GL_ERROR;
	}

	void point_light::translate(const glm::vec3& translation)
	{
		// Translate the point
		data.position += translation;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec3), &data.position);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void point_light::set_range(float range)
	{
		// Calculate the attenutation
		data.attenuation = glm::vec3(1.0f, 2.0f / range, 1.0f / (range * range));
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), sizeof(glm::vec3), &data.attenuation);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void point_light::set_colour(const glm::vec4& colour)
	{
		// Set the colour value
		data.colour = colour;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), &data.colour);
		// Display any errors
		CHECK_GL_ERROR;
	}

	bool point_light::build()
	{
		// Generate the buffer
		glGenBuffers(1, &buffer);
		// Bind
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		// Set the buffer data
		glBufferData(GL_UNIFORM_BUFFER, sizeof(point_light_data), &data, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		return !CHECK_GL_ERROR;
	}

	void spot_light::translate(const glm::vec3& translation)
	{
		// Translate the position
		data.position += translation;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec3), &data.position);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void spot_light::rotate(const glm::vec3& rotation)
	{
		// Create quaternion
		glm::quat q(rotation);
		// Call rotate for quaternion
		rotate(q);
	}

	void spot_light::rotate(const glm::quat& rotation)
	{
		// Calculate the new orientation
		auto rot = glm::mat3_cast(rotation);
		data.direction = rot * data.direction;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), sizeof(glm::vec3), &data.direction);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void spot_light::set_colour(const glm::vec4& colour)
	{
		// Set the colour
		data.colour = colour;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), &data.colour);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void spot_light::set_range(float range)
	{
		// Calculate the attenutation
		data.attenuation = glm::vec3(1.0f, 2.0f / range, 1.0f / (range * range));
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec4), sizeof(glm::vec3), &data.attenuation);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void spot_light::set_power(float power)
	{
		// Set the power
		data.power = power;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec4) + sizeof(glm::vec3), sizeof(float), &data.power);
		// Display any errors
		CHECK_GL_ERROR;
	}

	bool spot_light::build()
	{
		// Generate the buffer
		glGenBuffers(1, &buffer);
		// Bind
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		// Set the buffer data
		glBufferData(GL_UNIFORM_BUFFER, sizeof(spot_light_data), &data, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		return !CHECK_GL_ERROR;
	}

	void dynamic_lights::translate_point(int index, const glm::vec3& translation)
	{
		// Update the position
		data.point_lights[index].position += translation;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, index * sizeof(point_light_data) + sizeof(glm::vec4), sizeof(glm::vec3), &data.point_lights[index].position);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void dynamic_lights::set_range_point(int index, float range)
	{
		// Calculate the attenutation
		data.point_lights[index].attenuation = glm::vec3(1.0f, 2.0f / range, 1.0f / (range * range));
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, index * sizeof(point_light_data) + 2 * sizeof(glm::vec4), sizeof(glm::vec3), &data.point_lights[index].attenuation);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void dynamic_lights::set_colour_point(int index, const glm::vec4& colour)
	{
		// Update the colour
		data.point_lights[index].colour = colour;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, index * sizeof(point_light_data), sizeof(glm::vec4), &data.point_lights[index].colour);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void dynamic_lights::translate_spot(int index, const glm::vec3& translation)
	{
		// Translate the spot
		data.spot_lights[index].position += translation;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER,
			data.point_lights.size() * sizeof(point_light_data) + index * sizeof(spot_light_data) + sizeof(glm::vec4),
			sizeof(glm::vec3),
			&data.spot_lights[index].position);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void dynamic_lights::rotate_spot(int index, const glm::vec3& rotation)
	{
		// Create quaternion
		glm::quat q(rotation);
		// Call quaternion version
		rotate_spot(index, q);
	}

	void dynamic_lights::rotate_spot(int index, const glm::quat& rotation)
	{
		// Rotate direction
		auto rot = glm::mat3_cast(rotation);
		data.spot_lights[index].direction = rot * data.spot_lights[index].direction;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER,
			data.point_lights.size() * sizeof(point_light_data) + index * sizeof(spot_light_data) + 2 * sizeof(glm::vec4),
			sizeof(glm::vec3),
			&data.spot_lights[index].position);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void dynamic_lights::set_colour_spot(int index, const glm::vec4& colour)
	{
		// Set the colour
		data.spot_lights[index].colour = colour;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER,
			data.point_lights.size() * sizeof(point_light_data) + index * sizeof(spot_light_data),
			sizeof(glm::vec4),
			&data.spot_lights[index].colour);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void dynamic_lights::set_range_spot(int index, float range)
	{
		// Calculate the attenutation
		data.point_lights[index].attenuation = glm::vec3(1.0f, 2.0f / range, 1.0f / (range * range));
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER,
			data.point_lights.size() * sizeof(point_light_data) + index * sizeof(spot_light_data) + 3 * sizeof(glm::vec4),
			sizeof(glm::vec3),
			&data.spot_lights[index].attenuation);
		// Display any errors
		CHECK_GL_ERROR;
	}

	void dynamic_lights::set_power_spot(int index, float power)
	{
		// Set the power
		data.spot_lights[index].power = power;
		// Check if buffer
		if (!buffer)
			return;
		// Change the buffer data
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER,
			data.point_lights.size() * sizeof(point_light_data) + index * sizeof(spot_light_data) + 3 * sizeof(glm::vec4) + sizeof(glm::vec3),
			sizeof(float),
			&data.spot_lights[index].power);
		// Display any errors
		CHECK_GL_ERROR;
	}

	bool dynamic_lights::build()
	{
		// Generate the buffer
		glGenBuffers(1, &buffer);
		// Bind
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		// Set the buffer data - first create buffer
		glBufferData(GL_UNIFORM_BUFFER,
			data.point_lights.size() * sizeof(point_light_data) + data.spot_lights.size() * sizeof(spot_light_data),
			nullptr,
			GL_STATIC_DRAW);
		// Now set the data
		glBufferSubData(GL_UNIFORM_BUFFER,
			0,
			data.point_lights.size() * sizeof(point_light_data),
			&data.point_lights[0]);
		glBufferSubData(GL_UNIFORM_BUFFER,
			data.point_lights.size() * sizeof(point_light_data),
			data.spot_lights.size() * sizeof(spot_light_data),
			&data.spot_lights[0]);
		return !CHECK_GL_ERROR;
	}
}