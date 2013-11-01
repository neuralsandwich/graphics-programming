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
	registerCamera(ecam);

	arc_ball_camera scam = arc_ball_camera();
	// Use this to set the camera projection matrix
	scam.set_projection(quarter_pi<float>(), // FOV
						aspect,              // Aspect ratio
						0.2f,                // Near plane
		                10000.0f);           // Far plane
	// Set the camera properties
	scam.set_target(vec3(0.0, 0.0, 280.0));
	scam.set_distance(20.0f);
	registerCamera(scam);

	arc_ball_camera mcam = arc_ball_camera();
	// Use this to set the camera projection matrix
	scam.set_projection(quarter_pi<float>(), // FOV
						aspect,              // Aspect ratio
						0.2f,                // Near plane
		                10000.0f);           // Far plane
	// Set the camera properties
	scam.set_target(vec3(-1000.0, 0.0, -1000.0));
	scam.set_distance(200.0f);
	registerCamera(mcam);

	currentCamera = make_shared<arc_ball_camera>(cameras.at(0));

	// Set the view matrix
	auto view = lookAt(vec3(20.0f, 20.0f, 20.0f), // Camera position
		               vec3(0.0f, 0.0f, 0.0f),    // Target
		               vec3(0.0f, 1.0f, 0.0f));   // Up vector

	renderer::get_instance().set_view(view);

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
		currentCamera->rotate(-quarter_pi<float>() * deltaTime, 0.0f);

	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_LEFT)) {
		currentCamera->rotate(quarter_pi<float>() * deltaTime, 0.0f);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_UP)) {
		currentCamera->rotate(0.0f, quarter_pi<float>() * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_DOWN)) {
		currentCamera->rotate(0.0f, -quarter_pi<float>() * deltaTime);
	}
	/*if (glfwGetKey(renderer::get_instance().get_window(), 'W')) {
		currentCamera->move(vec3(0.0, 0.0, -5.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'S')) {
		currentCamera->move(vec3(0.0, 0.0, 5.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'A')) {
		currentCamera->move(vec3(-5.0, 0.0, 0.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'D')) {
		currentCamera->move(vec3(5.0, 0.0, 0.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_LEFT_SHIFT)) {
		currentCamera->move(vec3(0.0, 2.5, 0.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_LEFT_CONTROL)) {
		currentCamera->move(vec3(0.0, -2.5, 0.0) * deltaTime);
	}*/
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