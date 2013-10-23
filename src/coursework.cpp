/*
 * Introduction to graphics programming - SET09115 Coursework
 * Sean Jones, 10004520
 */

#include <render_framework\render_framework.h>
#include <chrono>
#include "scenemanager.h"
#include "cameramanager.h"

#pragma commet (lib, "Render Framework");

using namespace std;
using namespace glm;
using namespace render_framework;
using namespace chrono;

bool initialize() {

	// Initialize the renderer
	if (!renderer::get_instance().initialise()) {
		printf("Renderer failed to initialize.");
		return false;
	}

	// Set the clear colour to cyan
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	// Load Camera manager
	if (!CameraManager::get_instance().initialize()) {
		printf("Camera manager failed to initialize.");
		return false;
	}

	// Load Content manager
	if (!SceneManager::get_instance().initialize()) {
		printf("Scene manager failed to initialize.");
		return false;
	}

	return true;
}

int main (int argc,char *argv[]) {

	// Initialize needed managers and the render_framework
	if(!initialize()) {
		printf("Initialization Fail.");
		return -1;
	} else {
		printf("Initialization complete!");
	}

	// Monitor the elapsed time per frame
	auto currentTimeStamp = system_clock::now();
	auto prevTimeStamp = system_clock::now();

	// Main render loop
	while (renderer::get_instance().is_running())
	{
		// Get current time
		currentTimeStamp = system_clock::now();
		// Calculate elapsed time
		auto elapsed = duration_cast<milliseconds>(currentTimeStamp - prevTimeStamp);
		// Convert to fractions of a second
		auto seconds = float(elapsed.count()) / 1000.0;

		// Update Scene
		SceneManager::get_instance().update(seconds);

		// Check if running
		if (renderer::get_instance().begin_render())
		{
			// Render scene objects
			SceneManager::get_instance().render_scene();

		}

		prevTimeStamp = currentTimeStamp;

	} // Main render loop

	return 0;
}