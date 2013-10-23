#include "Cameramanager.h"

bool CameraManager::initialize()
{
	return true;
}


/*
 * Shuts down the CameraManagers
 */
void CameraManager::shutdown()
{
	// Set running to false
	_running = false;
}