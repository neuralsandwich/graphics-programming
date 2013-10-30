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

	CameraManager::get_instance().getCameraAtIndex(0).set_target(ContentManager::get_instance().getPropAt(0).trans.position);
	CameraManager::get_instance().update(deltaTime);
	ContentManager::get_instance().getPropAt(0).mat->set_uniform_value("eye_position", CameraManager::get_instance().currentCamera->get_position());
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
			shared_ptr<mesh> prop = make_shared<mesh>(ContentManager::get_instance().getPropAt(0));
			renderer::get_instance().render(prop);
			cout << "-- Camera Details --" << endl;
			cout << "Position: " << CameraManager::get_instance().currentCamera->get_position().x << " "
				 << CameraManager::get_instance().currentCamera->get_position().y << " "
				 << CameraManager::get_instance().currentCamera->get_position().z << "\n";
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