// Lesson 13.cpp : Defines the entry point for the console application.

#include <render_framework\render_framework.h>
#include <chrono>
#pragma comment (lib , "Render Framework" )

using namespace std;
using namespace glm;
using namespace render_framework;
using namespace chrono;

// Global scop box
shared_ptr<mesh> box;
// Keep track of current mode
int MODE = 0;


/*
 * key_callback
 *
 * used for identifying key presses
 * and switching the current mode
 */
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {

    switch (MODE) {
      case 0:
        MODE = 1;
        break;
      case 1:
        MODE = 2;
        break;
      case 2:
        MODE = 0;
        break;
      default:
        MODE = 0;
        break;
    }
  }

} // key_callback

/*
 * userTranslation
 *
 * Moves the object around inside the window using the keyboard arrow keys.
 */
void userTranslation(float deltaTime)
{
	// Move the quad when arrow keys are pressed
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_RIGHT)) {
		box->trans.translate(vec3(10.0, 0.0, 0.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_LEFT)) {
		box->trans.translate(vec3(-10.0, 0.0, 0.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_UP)) {
		box->trans.translate(vec3(0.0, 0.0, -10.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_DOWN)) {
		box->trans.translate(vec3(0.0, 0.0, 10.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'W')) {
		box->trans.translate(vec3(0.0, 10.0, 0.0) * deltaTime);
	}
	if (glfwGetKey(renderer::get_instance().get_window(), 'S')) {
		box->trans.translate(vec3(0.0, -10.0, 0.0) * deltaTime);
	}
} // userTranslation()

/*
 * Update routine
 *
 * Updates the application state
 */
void update(float deltaTime)
{
	switch (MODE) {
	case 0:
		userTranslation(deltaTime);
		break;
//    case 1:
//      userRotation(deltaTime);
//      break;
//    case 2:
//      userScale(deltaTime);
//      break;
	default:
		break;
	}
} // update()


int main()
{
	// Initialize the renderer
	if (!renderer::get_instance().initialise()) return -1;

	// Set the clear colour to cyan
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	/* Set the projection matrix */
	// First get the aspect ratio (width/height)
	float aspect = (float)renderer::get_instance().get_screen_width() /
					(float)renderer::get_instance().get_screen_width();
	// Use this to create projection matrix
	auto projection = perspective(
						degrees(quarter_pi<float>()),	// FOV
						aspect,							// Aspect ratio
						2.414f,							// Near plane
						10000.0f);						// Far plane
	// Set the projection matrix
	renderer::get_instance().set_projection(projection);

	// Set the view matrix
	auto view = lookAt(
					vec3(20.0f, 20.0f, 20.0f),	// Camera position
					vec3(0.0f, 0.0f, 0.0f),		// Target
					vec3(0.0f, 1.0f, 0.0f));	// Up vector
	renderer::get_instance().set_view(view);

	// Create box
	box = make_shared<mesh>();
	box->geom = geometry_builder::create_box();

	
	// Load in effect.  Start with shaders
	auto eff = make_shared<effect>();
	eff->add_shader("shader.vert", GL_VERTEX_SHADER);
	eff->add_shader("shader.frag", GL_FRAGMENT_SHADER);
	if (!effect_loader::build_effect(eff)) {
		return -1;
	}

	// Create material for box
	box->mat = make_shared<material>();
	box->mat->effect = eff;

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
			renderer::get_instance().render(box);

			// End the render
			renderer::get_instance().end_render();
		}

		prevTimeStamp = currentTimeStamp;

	} // Main render loop
}
