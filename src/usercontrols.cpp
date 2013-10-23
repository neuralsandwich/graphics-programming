#include "usercontrols.h"
#include <iostream>
#include <GLM\glm.hpp>
#include <render_framework\render_framework.h>

using namespace std;
using namespace render_framework;
using namespace glm;

void UserControls::moveCamera (free_camera* cam, float deltaTime) {
	if (glfwGetKey(renderer::get_instance().get_window(), 'W')) {
		cam->move(vec3(0.0, 0.0, -5.0) * deltaTime);
		if (glfwGetKey(renderer::get_instance().get_window(), 'S')) {
			cam->move(vec3(0.0, 0.0, 5.0) * deltaTime);
		}
		if (glfwGetKey(renderer::get_instance().get_window(), 'A')) {
			cam->move(vec3(-5.0, 0.0, 0.0) * deltaTime);
		}
		if (glfwGetKey(renderer::get_instance().get_window(), 'D')) {
			cam->move(vec3(5.0, 0.0, 0.0) * deltaTime);
		}
		if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_LEFT_SHIFT)) {
			cam->move(vec3(0.0, 5.0, 0.0) * deltaTime);
		}
		if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_LEFT_CONTROL)) {
			cam->move(vec3(0.0, 5.0, 0.0) * deltaTime);
		}
	}
} // moveCamera()

void UserControls::rotateCamera(free_camera* cam, float deltaTime) {
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_LEFT)) {
		cam->rotate(half_pi<float>() * deltaTime, 0.0);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_RIGHT)) {
		cam->rotate(-half_pi<float>() * deltaTime, 0.0);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_UP)) {
		cam->rotate(0.0, half_pi<float>() * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_DOWN)) {
		cam->rotate(0.0, -half_pi<float>() * deltaTime);
	}
} //rotateCamera