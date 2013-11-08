#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace render_framework
{
	/*
	Data structure representing an object transform in the world
	*/
	struct transform
	{
		// The position of the object in the world
		glm::vec3 position;
		// The orientation of the object in the world
		glm::quat orientation;
		// The scale of the object in the world
		glm::vec3 scale;

		// Creates a transform object.  Ensures scale is set to 1
		transform() : scale(glm::vec3(1.0f, 1.0f, 1.0f)) { }

		/*
		Translates (moves) the object in the world
		*/
		void translate(const glm::vec3& translation)
		{
			// Simply add the translation vector to the position
			position += translation;
		}

		/*
		Rotates the object by the given angle (in radians) around the given
		axis
		*/
		void rotate(float angle, const glm::vec3& axis)
		{
			// Simply rotate the quaternion
			orientation = glm::rotate(orientation, glm::degrees(angle), axis);
			// Normalize the quaternion, ensuring stability of value
			orientation = glm::normalize(orientation);
		}

		/*
		Rotates the object by the given Euler angles in a vec3 form
		*/
		void rotate(const glm::vec3& rotation)
		{
			// Convert Euler angles to a quaternion
			glm::quat rot(rotation);
			// Now simply multiply the orientation by the rotation
			orientation = orientation * rot;
			// Normalize the quaternion, ensuring stability of value
			orientation = glm::normalize(orientation);
		}

		/*
		Rotates the object by the given quaternion
		*/
		void rotate(const glm::quat& rotation)
		{
			// Simply multiply the orientation by the rotation
			orientation = orientation * rotation;
			// Normalize the quaternion, ensuring stability of value
			orientation = glm::normalize(orientation);
		}

		/*
		Gets the 4 x 4 transformation matrix for the object.
		*/
		glm::mat4 get_transform_matrix()
		{
			// Create translation matrix
			glm::mat4 matrix = glm::translate(glm::mat4(1.0f), position);
			// Scale the matrix
			matrix = glm::scale(matrix, scale);
			// Create rotation matrix
			glm::mat4 rotMatrix = glm::mat4_cast(orientation);
			// Multiply scaled translation by the rotation matrix
			// So we have T x S x R
			matrix *= rotMatrix;
			// Return the matrix
			return matrix;
		}

		/*
		Gets the 3 x 3 normal matrix for the object
		*/
		glm::mat3 get_normal_matrix()
		{
			// The transform only uses affine matrices.  Simply return the
			// rotation matrix
			return glm::mat3_cast(orientation);
		}
	};
}