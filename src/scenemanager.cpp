/** Top Level manager for the program. 
 * 
 * #include "scenemanger.h"		header for this class
 * #include "cameramanager.h"   header for CameraManager
 * #include "contentmanager.h"	header for ContentManager
 *
 * SceneManager controls both the Content and Camera manager for this program.
 * 
 * initialise() initialses the needed managers and any needed data.
 * updateScene() updates the camera position and the objects.
 */

#include "scenemanager.h"

#include <render_framework\render_framework.h>
#include <iostream>
#include <GLM\glm.hpp>

#include "cameramanager.h"
#include "contentmanager.h"

using namespace std;
using namespace render_framework;
using namespace glm;

/** initialize() : Initializes the scene manager
 * 
 * The render framework is initialised, setting the claire colour and then
 * updating the scene to apply the new colour. The lighting and CameraManager
 * are then initialised. The default camera is then set for the renderer and
 * finally the ContentManager is initialised.
 * 
 */
bool SceneManager::initialize()
{
	// Initialize the renderer
	if (!renderer::get_instance().initialise()) {
		printf("Renderer failed to initialize.\n");
		return false;
	}

	// Set Scene Clear colour to cyan Then render the blue background, just
	// something nicer to look at While we load everything else.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	render_scene(0.0);

	// Initialise the scenes lighting.
	if (!initialize_lighting()) {
		cout << "Lighting failed to initialize.\n";
		return false;
	}

	// Load Camera manager
	if (!CameraManager::get_instance().initialize()) {
		cout << "Camera manager failed to initialize.\n";
		return false;
	}

	// Set the renderer camera to default.
	renderer::get_instance().set_camera(
		CameraManager::get_instance().currentCamera);

	// Load Content manager.
	if (!ContentManager::get_instance().initialize()) {
		cout << "Content manager failed to initialize.\n";
		return false;
	}

	_focus = vec3(0.0, 0.0, 0.0);
	_running = true;

	return true;
} // initialize()

/** initialize_lighting() : Intialises light data.
 *
 */
bool SceneManager::initialize_lighting() {
	light = make_shared<directional_light>();
	light->data.ambient_intensity = vec4(0.1, 0.1, 0.1, 1.0);
	light->data.colour = vec4(1.0, 1.0, 1.0, 1.0);
	light->data.direction = normalize(vec3(-1.0, 0.0, 1.0));
	if (!light->build()) {
		return false;
	}

	return true;
} // Initialize_ligting()

/*
 * Updates all registers objects in the scene
 */
void SceneManager::update_scene(float deltaTime)
{
	printf("Updating scene.\n");

	// Move the camera when keys are pressed
	// Earth Cam
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_1)) {
		CameraManager::get_instance().setRenderCamera(CameraManager::get_instance().getCameraAtIndex(0));
		_focus = ContentManager::get_instance().get_prop_at(0)->get_mesh(0).trans.position;
		CameraManager::get_instance().currentCamera->set_distance(300.0f);
		CameraManager::get_instance().currentCamera->set_rotationY(0.336f);
	}
	// Sputnik Cam
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_2)) {
		CameraManager::get_instance().setRenderCamera(CameraManager::get_instance().getCameraAtIndex(1));
		_focus = ContentManager::get_instance().get_prop_at(1)->get_mesh(0).trans.position;
		CameraManager::get_instance().currentCamera->set_distance(5.0f);
		CameraManager::get_instance().currentCamera->set_rotationY(-0.1000f);
		CameraManager::get_instance().currentCamera->set_rotationY(0.4578f);
	}
	// Moon Cam
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_3)) {
		CameraManager::get_instance().setRenderCamera(CameraManager::get_instance().getCameraAtIndex(2));
		_focus = ContentManager::get_instance().get_prop_at(2)->get_mesh(0).trans.position;
		CameraManager::get_instance().currentCamera->set_distance(100.0f);
	}

	CameraManager::get_instance().currentCamera->set_target(_focus);
	CameraManager::get_instance().update(deltaTime);

	int i;
	for (i=0; i < ContentManager::get_instance().prop_list_size(); ++i) {
		ContentManager::get_instance().get_prop_at(i)->get_mesh(0).mat->set_uniform_value("eye_position", CameraManager::get_instance().currentCamera->get_position());
	}

	ContentManager::get_instance().update(deltaTime);
} // update_scene()

/*
* Render registered objects
*/
void SceneManager::render_scene(float deltaTime)
{
	printf("## Rendering ##\n");

	if (renderer::get_instance().begin_render())
	{
		int i, j;
		for (i = 0; i < ContentManager::get_instance().prop_list_size(); ++i) {
			for (j = 0; j < ContentManager::get_instance().get_prop_at(i)->mesh_size(); ++j) {
				shared_ptr<mesh> prop = make_shared<mesh>(ContentManager::get_instance().get_prop_at(i)->get_mesh(j));
				renderer::get_instance().render(prop);
			}
		}
	}
	// End the render
	renderer::get_instance().end_render();
} // render_scene(float deltaTime)

/*
* Shuts down the SceneManagers
*/
void SceneManager::shutdown()
{
	// Set running to false
	_running = false;
} // shutdown()