#include "camera.h"
#include <glm\gtx\euler_angles.hpp>

namespace render_framework
{
	/*
	Updates the target camera.  Delta time is not used
	*/
	void target_camera::update(float deltaTime)
	{
		// Forward vector is the vector from camera position to the target
		glm::vec3 forward = _target - _position;
		// Side vector is orthogonal to standard up vector and forward vector.
		// Use cross product to get orthogonal vector
		glm::vec3 side = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward);
		// We can now calculate the true up vector (used for camera orientation)
		// from the side and forward vectors.  True up will be orthogonal to both
		// these vectors.  We have essentially calculated the orthogonal basis
		_up = glm::cross(forward, side);
		// Up vector must be 1 unit long.  Normalize
		_up = glm::normalize(_up);
		// We can now set the view matrix
		_view = glm::lookAt(_position, _target, _up);
	}

	/*
	Updates the free camera.  Delta time is not used.
	*/
	void free_camera::update(float deltaTime)
	{
		// First, rotate the translation vector by the orientation.  This can
		// be done easily by multiplying the orientation quaternion by the
		// translation vector
		_translation = _orientation * _translation;
		// Add the translation vector to the position of the camera.
		_position += _translation;
		// Set the translation vector to zero
		_translation = glm::vec3(0.0f, 0.0f, 0.0f);

		// Now calculate the forward vector.  Start with normal forward and
		// then rotate by the orientation.  OpenGL, forward is -1 on Z component
		glm::vec3 forward = _orientation * glm::vec3(0.0f, 0.0f, -1.0f);

		// Target vector is just our position vector plus forward vector
		_target = _position + forward;

		// Now calculate up vector using same technique as forward vector
		_up = _orientation * glm::vec3(0.0f, 1.0f, 0.0f);
		
		// We can now calculate the view matrix
		_view = glm::lookAt(_position, _target, _up);
	}

	/*
	Rotates the camera round the Y axis (yaw) and X axis (pitch)
	*/
	void free_camera::rotate(float deltaYaw, float deltaPitch)
	{
		// We simply rotate the orientation quaternion by the two rotation values
		_orientation = glm::rotate(_orientation, glm::degrees(deltaYaw), glm::vec3(0.0f, 1.0f, 0.0f));
		_orientation = glm::rotate(_orientation, glm::degrees(deltaPitch), glm::vec3(1.0f, 0.0f, 0.0f));
		// Normalize the orientation.  Better stability
		_orientation = glm::normalize(_orientation);
	}

	/*
	Moves the free camera.  This is used in the update with the orientation to 
	calculate actual movement
	*/
	void free_camera::move(const glm::vec3& translation)
	{
		// Just add translation vector to current translation
		_translation += translation;
	}

	/*
	Updates the chase camera.  Delta time is not used
	*/
	void chase_camera::update(float deltaTime)
	{
		// Calculate the combined rotation as a quaternion
		glm::quat rotation(_targetRotation + _relativeRotation);
		
		// Now calculate the desired position (position if there was no 
		// springiness between target and camera)
		glm::vec3 desiredPosition = _targetPosition + (rotation * _positionOffset);
		// Out position lies somewhere between our current position and the
		// desired position (depending on springiness)
		_position = glm::mix(_position, desiredPosition, _springiness);

		// Calculate new target offset based on rotation
		_targetOffset = rotation * _targetOffset;
		// Target is then the target position plus this offset
		_target = _targetPosition + _targetOffset;

		// Calculate up vector based on rotation
		_up = rotation * glm::vec3(0.0f, 1.0f, 0.0f);

		// Calculate view matrix
		_view = glm::lookAt(_position, _target, _up);
	}

	/*
	Moves the chase camera by changing the target's position and rotation
	*/
	void chase_camera::move(const glm::vec3& newTargetPosition, const glm::vec3& newTargetRotation)
	{
		_targetPosition = newTargetPosition;
		_targetRotation = newTargetRotation;
	}

	/*
	Rotates the chase camera relative to its target
	*/
	void chase_camera::rotate(const glm::vec3& deltaRotation)
	{
		_relativeRotation += deltaRotation;
	}

	/*
	Updates the arc ball camera.  Does not use deltaTime
	*/
	void arc_ball_camera::update(float deltaTime)
	{
		// Generate a quaternion from the rotation
		glm::quat rotation(glm::vec3(_rotX, _rotY, 0.0f));
		// Multiply the rotation by translation vector to generate position
		_position = _target + (rotation * glm::vec3(0.0f, 0.0f, _distance));

		// Up is standard up multiplied by rotation
		_up = rotation * glm::vec3(0.0f, 1.0f, 0.0f);

		// Now calculate view matrix
		_view = glm::lookAt(_position, _target, _up);
	}

	/*
	Moves the camera by modifying the distance to the target
	*/
	void arc_ball_camera::move(float magnitude)
	{
		_distance += magnitude;
	}

	/*
	Rotates the camera around the target
	*/
	void arc_ball_camera::rotate(float deltaX, float deltaY)
	{
		_rotX += deltaX;
		_rotY += deltaY;
	}

	/*
	Moves the camera by modifying its target
	*/
	void arc_ball_camera::translate(const glm::vec3& translation)
	{
		_target += translation;
	}
}