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
    chase_camera cam = chase_camera();
    /* Set the projection matrix */
    // First get the aspect ratio (width/height)
    float aspect = (float)renderer::get_instance().get_screen_width()
                 / (float)renderer::get_instance().get_screen_width();
    // Use this to set the camera projection matrix
    cam.set_projection(quarter_pi<float>(), // FOV
                       aspect,              // Aspect ratio
                       2.414f,              // Near plane
                       10000.0f);           // Far plane
    // Set the camera properties
    cam.set_position(vec3(100.0, 100.0, 100.0));
    cam.set_springiness(0.001);
    cam.set_position_offset(vec3(200.0, 200.0, 200.0));

    registerCamera(cam);

    currentCamera = make_shared<chase_camera>(cameras.at(0));

    // Set the view matrix
    auto view = lookAt(vec3(20.0f, 20.0f, 20.0f), // Camera position
                       vec3(0.0f, 0.0f, 0.0f),    // Target
                       vec3(0.0f, 1.0f, 0.0f));   // Up vector

    renderer::get_instance().set_view(view);

    printf("Camera manager initialized.\n");

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