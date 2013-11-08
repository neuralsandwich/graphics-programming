#include "Cameramanager.h"

#include <render_framework\render_framework.h>
#include <GLM\glm.hpp>

#include "scenemanager.h"
#include "contentmanager.h"

using namespace std;
using namespace render_framework;
using namespace glm;

bool CameraManager::initialize()
{
	/* Set the projection matrix */
	// First get the aspect ratio (width/height)
	float aspect = (float)renderer::get_instance().get_screen_width()
		/ (float)renderer::get_instance().get_screen_height();

	// Set Earth Camera
	arc_ball_camera ecam = arc_ball_camera();
	// Use this to set the camera projection matrix
	ecam.set_projection(quarter_pi<float>(), // FOV
		aspect,              // Aspect ratio
		0.2f,                // Near plane
		10000.0f);           // Far plane
	// Set the camera properties
	ecam.set_target(vec3(0.0,0.0,0.0));
	ecam.set_distance(300.0f);
	ecam.set_rotationY(0.336f);
	registerCamera(ecam);

	arc_ball_camera scam = arc_ball_camera();
	// Use this to set the camera projection matrix
	scam.set_projection(quarter_pi<float>(), // FOV
		aspect,              // Aspect ratio
		0.2f,                // Near plane
		10000.0f);           // Far plane
	// Set the camera properties
	registerCamera(scam);

	arc_ball_camera mcam = arc_ball_camera();
	// Use this to set the camera projection matrix
	mcam.set_projection(quarter_pi<float>(), // FOV
		aspect,              // Aspect ratio
		0.2f,                // Near plane
		10000.0f);           // Far plane
	// Set the camera properties
	registerCamera(mcam);

	currentCamera = make_shared<arc_ball_camera>(cameras.at(0));

	printf("Camera manager initialized.\n");

	return true;
}

// Update cameras
void CameraManager::update(float deltaTime) {
	// Update current camera position
	moveCamera(deltaTime);

	currentCamera->update(deltaTime);
}

void CameraManager::moveCamera(float deltaTime) {
	// Move the camera when keys are pressed
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_RIGHT)) {
		currentCamera->rotate(0.0f, quarter_pi<float>() * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_LEFT)) {
		currentCamera->rotate(0.0f, -quarter_pi<float>() * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_UP)) {
		currentCamera->move(-20.0f * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_DOWN)) {
		currentCamera->move(20.0f * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'W')) {
		currentCamera->rotate(quarter_pi<float>() * deltaTime, 0.0);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'S')) {
		currentCamera->rotate(-quarter_pi<float>() * deltaTime, 0.0);
	}
}

arc_ball_camera CameraManager::getCameraAtIndex(int index) {
	return cameras.at(index);
}

void CameraManager::setRenderCamera(arc_ball_camera cam) {
	currentCamera = make_shared<arc_ball_camera>(cam);
	renderer::get_instance().set_camera(currentCamera);
}

void CameraManager::registerCamera(arc_ball_camera cam) {
	cameras.push_back(cam);
}

void CameraManager::unregisterCamera(int index) {
	cameras.erase(cameras.begin()+index-1);
}

/*
* Shuts down the CameraManagers
*/
void CameraManager::shutdown()
{
	// Set running to false
	_running = false;
}