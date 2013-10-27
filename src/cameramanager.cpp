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
	// Initialize the camera
	chase_camera cam;

	cam.set_position(vec3(0.0, 0.0, -200.0));
	cam.set_target(vec3(0.0, 0.0, 0.0));

	createCamera(cam);
	currentCamera = make_shared<chase_camera>(getCameraAtIndex(0));

	// Create the projection matrix
	// get the aspect ration (Width/height)
	float aspect = (float)renderer::get_instance().get_screen_width()
		/ (float)renderer::get_instance().get_screen_height();

	// Use aspect to create projection matrix
	auto projection = perspective(degrees(quarter_pi<float>()), // FOV
		aspect,						// aspect ratio
		2.414f,						// Near plane
		10000.0f);					// far plane
	// Set the projection matrix
	renderer::get_instance().set_projection(projection);

	// Create the view matrix
	auto view = lookAt(vec3(20.0f, 20.0f, 20.0f),
		vec3(0.0f, 0.0f, 0.0),
		vec3(0.0f, 1.0, 0.0f));
	// Set the view matrix
	renderer::get_instance().set_view(view);



	printf("Camera manager initialized.\n");

	return true;
}

bool CameraManager::createCamera(chase_camera cam) {

	shared_ptr<chase_camera> myCam = make_shared<chase_camera>(cam);

	/* Set the projection matrix */
	// First get the aspect ratio (width/height)
	float aspect = (float)renderer::get_instance().get_screen_width()
		         / (float)renderer::get_instance().get_screen_width();
	// Use this to set the camera projection matrix
	myCam->set_projection(quarter_pi<float>(), // FOV
		aspect,              // Aspect ratio
		2.414f,              // Near plane
		10000.0f);           // Far plane
	myCam->set_springiness(0.001f);
	myCam->set_position_offset(vec3(0.0f, 10.f, 50.0f));
	registerCamera(*myCam);

	return true;
}

// Update cameras
void CameraManager::update(float deltaTime) {
	currentCamera->update(deltaTime);
}

chase_camera CameraManager::getCameraAtIndex(int index) {
	return cameras.at(index);
}

void CameraManager::setRenderCamera(chase_camera cam) {
	currentCamera = make_shared<chase_camera>(cam);
	renderer::get_instance().set_camera(make_shared<chase_camera>(cam));
}

void CameraManager::registerCamera(chase_camera cam) {
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