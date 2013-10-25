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
	printf("Camera manager initialized.\n");

	return true;
}


// Update cameras
void CameraManager::update(float deltaTime) {
}


/*
* Shuts down the CameraManagers
*/
void CameraManager::shutdown()
{
	// Set running to false
	_running = false;
}