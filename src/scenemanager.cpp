#include <render_framework\render_framework.h>
#include <iostream>
#include "scenemanager.h"

using namespace render_framework;

/*
* Initializes the scene manager
*/
bool SceneManager::initialize()
{
	_running = true;



	return true;
}

/*
* Updates all registers objects in the scene
*/
void SceneManager::update(float deltaTime)
{
	printf("Updating scene.\n");
}

/*
 * Register object with scene manager for rendering
 */
void SceneManager::registerObject(std::shared_ptr<mesh> object)
{
	propList.push_back(object);
}

/*
 * Unregister object with scene manager
 */
void SceneManager::unregisterObject(std::shared_ptr<mesh> object)
{
	propList.push_back(object);
}

/*
* Render registered objects
*/
void SceneManager::render_scene()
{
	printf("Here is your scene.\n");


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