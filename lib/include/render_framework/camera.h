#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>

namespace render_framework
{
	/*
	A abstract class defining a camera in our rendering system
	*/
	class camera
	{
	protected:
		// The position that the camera is in
		glm::vec3 _position;
		// The target of the camera (what it is looking at)
		glm::vec3 _target;
		// The orientation (up direction) of the camera
		glm::vec3 _up;
		// The view matrix defined for the camera
		glm::mat4 _view;
		// The projection matrix defined for the camera
		glm::mat4 _projection;
	public:
		// Camera constructor
		camera() { }
		// Camera destructor.  Virtual as this is a virtual class
		virtual ~camera() { }
		/*
		Updates the camera given a certain amount of elapsed time.  Time is not
		generally used, but left in for completeness
		*/
		virtual void update(float deltaTime) = 0;
		// Gets the position vector
		glm::vec3 get_position() const { return _position; }
		// Sets the position vector
		void set_position(const glm::vec3& value) { _position = value; }
		// Gets the target vector
		glm::vec3 get_target() const { return _target; }
		// Sets the target vector
		void set_target(const glm::vec3& value) { _target = value; }
		// Gets the up vector
		glm::vec3 get_up() const { return _up; }
		// Sets the up vector
		void set_up(const glm::vec3& value) { _up = value; }
		// Gets the view matrix
		glm::mat4 get_view() const { return _view; }
		// Gets the projection matrix
		glm::mat4 get_projection() const { return _projection; }
		// Sets the projection matrix
		void set_projection(float fov, float aspect, float near, float far)
		{
			_projection = glm::perspective(glm::degrees(fov), aspect, near, far);
		}
	};

	/*
	A camera which aims at a particular target.  Generally considered
	fixed
	*/
	class target_camera : public camera
	{
	public:
		// Target camera constructor
		target_camera() : camera() { }
		// Target camera destructor
		~target_camera() { }
		// Updates the camera
		void update(float deltaTime);
	};

	/*
	A camera which allows full free movement in the world
	*/
	class free_camera : public camera
	{
	private:
		// Quaternion representing the orientation of the camera
		glm::quat _orientation;
		// The translation of the camera since the last frame
		glm::vec3 _translation;
	public:
		// Free camera constructor
		free_camera() : camera() { }
		// Free camera destructor
		~free_camera() { }
		// Get the current orientation of the camera
		glm::quat get_orientation() const { return _orientation; }
		// Sets the orientation of the camera
		void set_orientation(const glm::quat& value) { _orientation = value; }
		// Updates the camera
		void update(float deltaTime);
		// Rotates the camera by the given yaw (y-axis rotation) and pitch
		// (x-axis rotation)
		void rotate(float deltaYaw, float deltaPitch);
		// Moves the camera.  Will be executed at the next update
		void move(const glm::vec3& translation);
	};

	/*
	A camera that will "chase" and object around the world.  Essentially
	a third person camera
	*/
	class chase_camera : public camera
	{
	private:
		// The position of the target being chased
		glm::vec3 _targetPosition;
		// The offset of the camera from its desired position
		glm::vec3 _positionOffset;
		// The rotation of the target being chased
		glm::vec3 _targetRotation;
		// The offset of the camera position to the target position
		glm::vec3 _targetOffset;
		// The rotation of the camera relative to the target
		glm::vec3 _relativeRotation;
		// Springiness factor on the camera
		float _springiness;
	public:
		// Chase camera constructor
		chase_camera() { }
		// Chase camera destructor
		~chase_camera() { }
		// Gets the position of the target
		glm::vec3 get_target_position() const { return _targetPosition; }
		// Sets the position of the target
		void set_target_position(const glm::vec3& value) { _targetPosition = value; }
		// Gets the position offset
		glm::vec3 get_position_offset() const { return _positionOffset; }
		// Sets the position of the target
		void set_position_offset(const glm::vec3& value) { _positionOffset = value; }
		// Gets the rotation of the target
		glm::vec3 get_target_rotation() const { return _targetRotation; }
		// Sets the rotation of the target
		void set_target_rotation(const glm::vec3& value) { _targetRotation  = value; }
		// Gets the offset from the target
		glm::vec3 get_target_offset() const { return _targetOffset; }
		// Sets the offset from the target
		void set_target_offset(const glm::vec3& value) { _targetOffset = value; }
		// Gets the camera's rotation relative to the target
		glm::vec3 get_relative_rotation() const { return _relativeRotation; }
		// Sets the camera's rotation relative to the target
		void set_relative_rotation(const glm::vec3& value) { _relativeRotation = value; }
		// Gets the springiness coefficient for the camera
		float get_springiness() const { return _springiness; }
		// Sets the springiness coefficient for the camera
		void set_springiness(float value) { _springiness = value; }
		// Updates the camera
		void update(float deltaTime);
		// Moves the camera by updating the target position and rotation
		void move(const glm::vec3& newTargetPosition, const glm::vec3& newTargetRotation);
		// Rotates the camera around the target
		void rotate(const glm::vec3& deltaRotation);
	};

	/*
	A camera that targets a particular object and allows rotation around
	it.  A distance value dictates how far from the target the camera is
	placed.
	*/
	class arc_ball_camera : public camera
	{
	private:
		// Rotation around the X axis of the target
		float _rotX;
		// Rotation around the Y axis of the target
		float _rotY;
		// Distance of the camera from the target
		float _distance;
	public:
		// Arc ball camera constructor
		arc_ball_camera() : _rotX(0.0f), _rotY(0.0f) { }
		// Arc ball camera destructor
		~arc_ball_camera() { }
		// Gets the rotation of the camera around the X axis
		float get_rotationX() const { return _rotX; }
		// Sets the rotation of the camera around the X axis
		void set_rotationX(float value) { _rotX = value; }
		// Gets the rotation of the camera around the Y axis
		float get_rotationY() const { return _rotY; }
		// Sets the rotation of the camera around the Y axis
		void set_rotationY(float value) { _rotY = value; }
		// Gets the distance of the camera from the target
		float get_distance() const { return _distance; }
		// Sets the distance of the camera from the target
		void set_distance(float value) { _distance = value; }
		// Updates the camera
		void update(float deltaTime);
		// Moves the camera relative to the target
		void move(float magnitude);
		// Rotates the camera around the target
		void rotate(float deltaX, float deltaY);
		// Moves the target position by the given vector
		void translate(const glm::vec3& translation);
	};
}