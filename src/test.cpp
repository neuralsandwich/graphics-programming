// Lesson 13.cpp : Defines the entry point for the console application.

#include <render_framework\render_framework.h>
#include <chrono>
#pragma comment (lib , "Render Framework" )

using namespace std;
using namespace glm;
using namespace render_framework;
using namespace chrono;

// Global scop box
shared_ptr<mesh> object[5];


/*
 * Update routine
 *
 * Updates the application state
 */
void update(float deltaTime) {} // update()


bool load_content() {

	int i = 0;
	for (i=0;i<4;i++) {
		// Create box
		object[i] = make_shared<mesh>();
		object[i]->geom = geometry_builder::create_box();


		// Load in effect.  Start with shaders
		auto eff = make_shared<effect>();
		eff->add_shader("shader.vert", GL_VERTEX_SHADER);
		eff->add_shader("shader.frag", GL_FRAGMENT_SHADER);
		if (!effect_loader::build_effect(eff)) {
			return false;
		}

		// Create material for box
		object[i]->mat = make_shared<material>();
		object[i]->mat->effect = eff;
		object[i]->mat->set_texture("tex", texture_loader::load("Checkered.png"));

		object[i]->trans.translate(vec3(0.0, (float) i*2+1, 0.0));
	}

	return true;

}


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

	if (!load_content()) {
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
			for (i = 0; i <4; i++) {
				renderer::get_instance().render(object[i]);
			}


			// End the render
			renderer::get_instance().end_render();
		}

		prevTimeStamp = currentTimeStamp;

	} // Main render loop
}
