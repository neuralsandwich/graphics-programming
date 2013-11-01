#include "scenemanager.h"

#include <render_framework\render_framework.h>
#include <iostream>
#include <GLM\glm.hpp>

#include "cameramanager.h"
#include "contentmanager.h"

using namespace std;
using namespace render_framework;
using namespace glm;

/*
* Initializes the scene manager
*/
bool SceneManager::initialize()
{
	cout << "## Initializing ##" << endl;
	// Initialize the renderer
	if (!renderer::get_instance().initialise()) {
		printf("Renderer failed to initialize.\n");
		return false;
	}

	// Set Scene Clear colour to cyan
	// Then render the blue background, just something nicer to look at
	// While we load everything else.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	renderScene(0.0);
	
	light = make_shared<directional_light>();
	light->data.ambient_intensity = vec4(0.1, 0.1, 0.1, 1.0);
	light->data.colour = vec4(1.0, 1.0, 1.0, 1.0);
	light->data.direction = normalize(vec3(-1.0, 0.0, 1.0));
	if (!light->build()) {
		return false;
	}

	// Load Camera manager
	if (!CameraManager::get_instance().initialize()) {
		printf("Camera manager failed to initialize.\n");
		return false;
	}

	renderer::get_instance().set_camera(CameraManager::get_instance().currentCamera);

	// Load Content manager
	if (!ContentManager::get_instance().initialize()) {
		printf("Content manager failed to initialize.\n");
		return false;
	}

	_focus = vec3(0.0, 0.0, 0.0);

	_running = true;

	cout << "## Initialization Complete ##" << endl;
	return true;
}

/*
* Updates all registers objects in the scene
*/
void SceneManager::updateScene(float deltaTime)
{
	printf("Updating scene.\n");

	// Move the camera when keys are pressed
	// Earth Cam
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_1)) {
		CameraManager::get_instance().setRenderCamera(CameraManager::get_instance().getCameraAtIndex(0));
		_focus = ContentManager::get_instance().getPropAt(0).trans.position;
        CameraManager::get_instance().currentCamera->set_distance(300.0f);
	}
	// Sputnik
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_2)) {
		CameraManager::get_instance().setRenderCamera(CameraManager::get_instance().getCameraAtIndex(1));
		_focus = ContentManager::get_instance().getPropAt(3).trans.position;
        CameraManager::get_instance().currentCamera->set_distance(5.0f);
	}
	// Moon
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_3)) {
		CameraManager::get_instance().setRenderCamera(CameraManager::get_instance().getCameraAtIndex(2));
		_focus = ContentManager::get_instance().getPropAt(7).trans.position;
        CameraManager::get_instance().currentCamera->set_distance(100.0f);
	}
	cout << _focus.x << " " << _focus.y << " "<< _focus.z << "\n" << endl;

	CameraManager::get_instance().currentCamera->set_target(_focus);
	CameraManager::get_instance().update(deltaTime);
	
	int i;
	for (i=0; i < ContentManager::get_instance().propListSize(); ++i) {
		ContentManager::get_instance().getPropAt(i).mat->set_uniform_value("eye_position", CameraManager::get_instance().currentCamera->get_position());
	}

	ContentManager::get_instance().update(deltaTime);
}


/*
* Render registered objects
*/
void SceneManager::renderScene(float deltaTime)
{
	printf("## Rendering ##\n");

	if (renderer::get_instance().begin_render())
	{
		int i;
		for (i = 0; i < ContentManager::get_instance().propListSize(); ++i) {
			shared_ptr<mesh> prop = make_shared<mesh>(ContentManager::get_instance().getPropAt(i));
			renderer::get_instance().render(prop);
			cout << "-- Camera Details --" << endl;
			cout << "Position: " << CameraManager::get_instance().currentCamera->get_position().x << " "
				 << CameraManager::get_instance().currentCamera->get_position().y << " "
				 << CameraManager::get_instance().currentCamera->get_position().z << "\n";
			cout << "Target: " << CameraManager::get_instance().currentCamera->get_target().x << " "
				 << CameraManager::get_instance().currentCamera->get_target().y << " "
				 << CameraManager::get_instance().currentCamera->get_target().z << "\n";
		}
	}
	// End the render
	renderer::get_instance().end_render();
}

/*
* Shuts down the SceneManagers
*/
void SceneManager::shutdown()
{
	// Set running to false
	_running = false;
}