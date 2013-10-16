// Lesson 13.cpp : Defines the entry point for the console application.

#include <render_framework\render_framework.h>
#include <chrono>
#pragma comment (lib , "Render Framework" )

using namespace std;
using namespace glm;
using namespace render_framework;
using namespace chrono;

#define OBJECTS 1

// Global scope box
shared_ptr<mesh> object[OBJECTS];
shared_ptr<target_camera> cam;
shared_ptr<mesh> plane;


/*
 * userTranslation
 *
 * Moves the object around inside the window using the keyboard arrow keys.
 */
void userTranslation(float deltaTime)
{
	// Move the quad when arrow keys are pressed
	if (glfwGetKey(renderer::get_instance().get_window(), 'J')) {
		object[0]->trans.translate(vec3(-10.0, 0.0, 0.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'L')) {
		object[0]->trans.translate(vec3(10.0, 0.0, 0.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'I')) {
		object[0]->trans.translate(vec3(0.0, 0.0, -10.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'K')) {
		object[0]->trans.translate(vec3(0.0, 0.0, 10.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'U')) {
		object[0]->trans.translate(vec3(0.0, 10.0, 0.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'O')) {
		object[0]->trans.translate(vec3(0.0, -10.0, 0.0) * deltaTime);
	}
} // userTranslation()


/*
 * cameraTranslation
 *
 * Moves the object around inside the window using the keyboard arrow keys.
 */
void cameraTranslation(float deltaTime)
{
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_UP)) {
		cam->set_position(cam->get_position() - 1.0f);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_DOWN)) {
		cam->set_position(cam->get_position() + 1.0f);
	}

} // cameraTranslation()


/*
 * Update routine
 *
 * Updates the application state
 */
void update(float deltaTime) {

	cameraTranslation(deltaTime);
	userTranslation(deltaTime);

	cam->set_target(object[0]->trans.position);
	cam->update(deltaTime);

} // update()


bool load_content() {

		// Create plane
		plane = make_shared<mesh>();
		object[0] = make_shared<mesh>();

		plane->geom = geometry_builder::create_plane();
		object[0]->geom = geometry_builder::create_sphere(20, 20, vec3(2, 2, 2));

		plane->trans.translate(vec3(0.0f, -1.0f, 0.0f));
		// Load in effect.  Start with shaders
		auto eff = make_shared<effect>();
		eff->add_shader("ambient.vert", GL_VERTEX_SHADER);
		eff->add_shader("ambient.frag", GL_FRAGMENT_SHADER);
		if (!effect_loader::build_effect(eff)) {
			return false;
		}
		// Attach effect to the plane mesh
		plane->mat = make_shared<material>();
		object[0]->mat = make_shared<material>();
		object[0]->mat->effect = eff;
		plane->mat->effect = eff;

		// Ambient intensity should be (0.3, 0.3, 0.3, 1.0)
		vec4 ambient_intensity = vec4(0.3, 0.3, 0.3, 1.0);
		vec4 blue_material = vec4(0.0, 0.0, 1.0, 1.0);
		vec4 red_material = vec4(1.0, 0.0, 0.0, 1.0);
		object[0]->mat->set_uniform_value("ambient_intensity", ambient_intensity);
		object[0]->mat->set_uniform_value("material_colour", blue_material);
		plane->mat->set_uniform_value("ambient_intensity", ambient_intensity);
		plane->mat->set_uniform_value("material_colour", red_material);

		object[0]->trans.translate(vec3(0.0, 2.0, 0.0));

	return true;

} // load_content()


bool load_camera() {
	// Initialize the camera
	cam = make_shared<target_camera>();

	/* Set the projection matrix */
	// First get the aspect ratio (width/height)
	float aspect = (float)renderer::get_instance().get_screen_width() /
					(float)renderer::get_instance().get_screen_width();
	// Use this to set the camera projection matrix
	cam->set_projection(
						quarter_pi<float>(),			// FOV
						aspect,							// Aspect ratio
						2.414f,							// Near plane
						10000.0f);						// Far plane
	// Set the camera properties
	cam->set_position(vec3(0.0, 5.0, 20.0));
	cam->set_target(vec3(0.0, 0.0, 0.0));
	cam->set_up(vec3(0.0, 1.0, 0.0));

	// Attach camera to renderer
	renderer::get_instance().set_camera(cam);

	// Set the view matrix
	auto view = lookAt(
					vec3(20.0f, 20.0f, 20.0f),	// Camera position
					vec3(0.0f, 0.0f, 0.0f),		// Target
					vec3(0.0f, 1.0f, 0.0f));	// Up vector
	renderer::get_instance().set_view(view);

	return true;
} // load_camera


int main()
{
	// Initialize the renderer
	if (!renderer::get_instance().initialise()) return -1;

	// Set the clear colour to cyan
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	if (!load_content()) {
		return -1;
	}

	if (!load_camera()) {
		return -1;
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
		update(seconds);

		// Check if running
		if (renderer::get_instance().begin_render())
		{
			// Render Cube
			int i = 0;
			for (i = 0; i <OBJECTS; i++) {
				renderer::get_instance().render(object[i]);
			}

			// Render plane
			renderer::get_instance().render(plane);

			// End the render
			renderer::get_instance().end_render();
		}

		prevTimeStamp = currentTimeStamp;

	} // Main render loop
}