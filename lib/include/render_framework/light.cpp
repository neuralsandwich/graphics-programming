#include "light.h"

namespace render_framework
{
	void directional_light::rotate(const glm::vec3& rotation)
	{
	}

	void directional_light::rotate(const glm::quat& rotation)
	{
	}

	void directional_light::set_ambient_intensity(const glm::vec4& ambient)
	{
	}

	void directional_light::set_colour(const glm::vec4& colour)
	{
	}

	void point_light::translate(const glm::vec3& translation)
	{
	}

	void point_light::set_range(float range)
	{
	}

	void point_light::set_colour(const glm::vec4& colour)
	{
	}

	void spot_light::translate(const glm::vec3& translation)
	{
	}

	void spot_light::rotate(const glm::vec3& rotation)
	{
	}

	void spot_light::rotate(const glm::quat& rotation)
	{
	}

	void spot_light::set_colour(const glm::vec4& colour)
	{
	}

	void spot_light::set_range(float range)
	{
	}

	void spot_light::set_power(float power)
	{
	}

	void dynamic_lights::translate_point(int index, const glm::vec3& translation)
	{
	}

	void dynamic_lights::set_range_point(int index, float range)
	{
	}

	void dynamic_lights::set_colour_point(int index, const glm::vec4& colour)
	{
	}

	void dynamic_lights::translate_spot(int index, const glm::vec3& translation)
	{
	}

	void dynamic_lights::rotate_spot(int index, const glm::vec3& rotation)
	{
	}

	void dynamic_lights::rotate_spot(int index, const glm::quat& rotation)
	{
	}

	void dynamic_lights::set_colour_spot(int index, const glm::vec4& colour)
	{
	}

	void dynamic_lights::set_range_spot(int index, float range)
	{
	}

	void dynamic_lights::set_power_spot(int index, float power)
	{
	}
}