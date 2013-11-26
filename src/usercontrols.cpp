#include "usercontrols.h"
#include <iostream>
#include <GLM\glm.hpp>
#include <render_framework\render_framework.h>

using namespace std;
using namespace render_framework;
using namespace glm;

void UserControls::moveCamera(shared_ptr<arc_ball_camera> cam, float deltaTime) {
	// Move the camera when keys are pressed
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_RIGHT)) {
		cam->rotate(0.0f, quarter_pi<float>() * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_LEFT)) {
		cam->rotate(0.0f, -quarter_pi<float>() * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_UP)) {
		cam->move(-20.0f * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_DOWN)) {
		cam->move(20.0f * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'W')) {
		cam->rotate(quarter_pi<float>() * deltaTime, 0.0);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'S')) {
		cam->rotate(-quarter_pi<float>() * deltaTime, 0.0);
	}
} // moveCamera()