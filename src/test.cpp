// Lesson 13.cpp : Defines the entry point for the console application.

#include <render_framework\render_framework.h>
#pragma comment (lib , "Render Framework" )

using namespace std;
using namespace glm;
using namespace render_framework;



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

	// Create Object
	auto object = geometry_builder::create_plane();

	// Main render loop
	while (renderer::get_instance().is_running())
	{
		// Check if running
		if (renderer::get_instance().begin_render())
		{
			// Render Cube
			renderer::get_instance().render(object);

			// End the render
			renderer::get_instance().end_render();
		}
	}
}

