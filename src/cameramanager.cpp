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
	arc_ball_camera cam = arc_ball_camera();
	/* Set the projection matrix */
	// First get the aspect ratio (width/height)
	float aspect = (float)renderer::get_instance().get_screen_width()
		         / (float)renderer::get_instance().get_screen_height();
	// Use this to set the camera projection matrix
	cam.set_projection(quarter_pi<float>(), // FOV
		aspect,              // Aspect ratio
		2.414f,              // Near plane
		10000.0f);           // Far plane
	// Set the camera properties
	cam.set_target(vec3(0.0, 0.0, 0.0));
	cam.set_distance(300.0f);

	registerCamera(cam);

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

	currentCamera->update(deltaTime);
}

arc_ball_camera CameraManager::getCameraAtIndex(int index) {
	return cameras.at(index);
}

void CameraManager::setRenderCamera(arc_ball_camera cam) {
	renderer::get_instance().set_camera(make_shared<arc_ball_camera>(cam));
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