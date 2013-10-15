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
shared_ptr<mesh> object[1];
shared_ptr<arc_ball_camera> cam;
shared_ptr<mesh> plane;
float dissolveFactor = 1.0f;


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
	// Move the quad when arrow keys are pressed
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_RIGHT)) {
		cam->rotate(0.0, half_pi<float>() * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_LEFT)) {
		cam->rotate(0.0, -half_pi<float>() * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_UP)) {
		cam->move(-5.0f * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_DOWN)) {
		cam->move(5.0f * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'W')) {
		cam->rotate(half_pi<float>() * deltaTime, 0.0);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'S')) {
		cam->rotate(-half_pi<float>() * deltaTime, 0.0);
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

	int i = 0;
	for (i=0;i<OBJECTS;i++) {
		// Create plane
		plane = make_shared<mesh>();
		plane->geom = geometry_builder::create_plane();
		plane->trans.translate(vec3(0.0f, -1.0f, 0.0f));
		// Load in effect.  Start with shaders
		auto eff = make_shared<effect>();
		eff->add_shader("shader.vert", GL_VERTEX_SHADER);
		eff->add_shader("shader.frag", GL_FRAGMENT_SHADER);
		if (!effect_loader::build_effect(eff)) {
			return false;
		}
		// Attach effect to the plane mesh
		plane->mat = make_shared<material>();
		plane->mat->effect = eff;
		// Set the texture for shader
		plane->mat->set_texture("tex", texture_loader::load("Checkered.png"));

		// Create box
		object[i] = make_shared<mesh>();
		object[i]->geom = geometry_builder::create_torus();

		// Load in effect.  Start with shaders
		auto eff2 = make_shared<effect>();
		eff2->add_shader("cell.vert", GL_VERTEX_SHADER);
		eff2->add_shader("cell.frag", GL_FRAGMENT_SHADER);
		if (!effect_loader::build_effect(eff2)) {
			return false;
		}
		// Attach effect to the object
		object[i]->mat = make_shared<material>();
		object[i]->mat->effect = eff2;
		// Set textures for shader
		vector<vec4> colour;
		colour.push_back(vec4(0.12f, 0.0f, 0.0f, 1.0f));
		colour.push_back(vec4(0.25f, 0.0f, 0.0f, 1.0));
		colour.push_back(vec4(0.5f, 0.0f, 0.0f, 1.0));
		colour.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0));
		auto tex = texture_generator::generate(colour, 4, 1, false, false);
		// Attach texture to the box effect

		object[i]->mat->set_texture("tex", tex);

	}

	return true;

} // load_content()


bool load_camera() {
	// Initialize the camera
	cam = make_shared<arc_ball_camera>();

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
	cam->set_position(vec3(0.0, 0.0, 0.0));
	cam->set_distance(20.0f);

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