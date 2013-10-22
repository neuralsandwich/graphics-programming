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
shared_ptr<free_camera> cam;
shared_ptr<mesh> plane;


/*
 * userRotation
 *
 * rotates the object
 */
void userRotation(float deltaTime) {

  if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_KP_8)) {
          object[0]->trans.rotate(vec3(-pi<float>(), 0.0, 0.0f) * deltaTime);
  }
  if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_KP_5)) {
          object[0]->trans.rotate(vec3(pi<float>(), 0.0, 0.0f) * deltaTime);
  }
  if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_KP_6)) {
          object[0]->trans.rotate(vec3(0.0, -pi<float>(), 0.0f) * deltaTime);
  }
  if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_KP_4)) {
          object[0]->trans.rotate(vec3(0.0, pi<float>(), 0.0f) * deltaTime);
  }
  if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_KP_7)) {
          object[0]->trans.rotate(vec3(0.0, 0.0, pi<float>()) * deltaTime);
  }
  if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_KP_9)) {
          object[0]->trans.rotate(vec3(0.0, 0.0, -pi<float>()) * deltaTime);
  }

} // userRotation


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
 * moveCamera
 *
 * Moves the object around inside the window using the keyboard arrow keys.
 */
void moveCamera(float deltaTime)
{
        // Move the quad when arrow keys are pressed
        if (glfwGetKey(renderer::get_instance().get_window(), 'W')) {
                cam->move(vec3(0.0, 0.0, -5.0) * deltaTime);
        }
        if (glfwGetKey(renderer::get_instance().get_window(), 'S')) {
                cam->move(vec3(0.0, 0.0, 5.0) * deltaTime);
        }
        if (glfwGetKey(renderer::get_instance().get_window(), 'A')) {
                cam->move(vec3(-5.0, 0.0, 0.0) * deltaTime);
        }
        if (glfwGetKey(renderer::get_instance().get_window(), 'D')) {
                cam->move(vec3(5.0, 0.0, 0.0) * deltaTime);
        }
        if (glfwGetKey(renderer::get_instance().get_window(), 'Q')) {
                cam->rotate(half_pi<float>() * deltaTime, 0.0);
        }
        if (glfwGetKey(renderer::get_instance().get_window(), 'E')) {
                cam->rotate(-half_pi<float>() * deltaTime, 0.0);
        }
        if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_UP)) {
                cam->rotate(0.0, half_pi<float>() * deltaTime);
        }
        if (glfwGetKey(renderer::get_instance().get_window(), GLFW_KEY_DOWN)) {
                cam->rotate(0.0, -half_pi<float>() * deltaTime);
        }
} // moveCamera()


/*
 * Update routine
 *
 * Updates the application state
 */
void update(float deltaTime) {

	moveCamera(deltaTime);
	userRotation(deltaTime);
	userTranslation(deltaTime);

	cam->set_target(object[0]->trans.position);
	cam->update(deltaTime);

} // update()


bool load_content() {

		// Create plane
		plane = make_shared<mesh>();
		object[0] = make_shared<mesh>();

		plane->geom = geometry_builder::create_plane();
		object[0]->geom = geometry_builder::create_sphere(256,256, vec3(2, 2, 2));

		plane->trans.translate(vec3(0.0f, -1.0f, 0.0f));
		// Load in effect.  Start with shaders
		auto eff = make_shared<effect>();
		eff->add_shader("phong.vert", GL_VERTEX_SHADER);
		eff->add_shader("phong.frag", GL_FRAGMENT_SHADER);
		if (!effect_loader::build_effect(eff)) {
			return false;
		}
		// Attach effect to the plane mesh
		plane->mat = make_shared<material>();
		plane->mat->effect = eff;
		object[0]->mat = make_shared<material>();
		object[0]->mat->effect = eff;

		// Set the values on material - blue plane and red sphere.
		// Both have white light colour.
		// light direction is away (1, 1, -1) normalized
		vec4 red_emissive = vec4(0.2f, 0.0f, 0.0f, 1.0f);
		vec4 blue_emissive = vec4(0.0f, 0.0f, 0.2f, 1.0f);
		vec4 ambient_intensity = vec4(0.3f, 0.3f, 0.3f, 1.0f);
		vec4 light_colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		vec3 light_direction = normalize(vec3(1.0f, 1.0f, 1.0f));
		vec4 blue_material = vec4(0.0f, 0.0f, 1.0f, 1.0f);
		vec4 red_material = vec4(1.0f, 0.0f, 0.0f, 1.0f);
		vec4 specular_colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		vec3 eye_position = cam->get_position();
		float shininess = 50.0f;
		
		// Set shader values for object
		object[0]->mat->data.emissive = red_emissive;
		object[0]->mat->data.diffuse_reflection = red_material;
		object[0]->mat->data.specular_reflection = specular_colour;
		object[0]->mat->data.shininess = shininess;
		object[0]->mat->set_uniform_value("eye_position", eye_position);
		// Set shader values for plane
		plane->mat->data.emissive = blue_emissive;
		plane->mat->data.diffuse_reflection = blue_material;
		plane->mat->data.specular_reflection = specular_colour;
		plane->mat->data.shininess = shininess;
		plane->mat->set_uniform_value("eye_position", eye_position);

		// Create light for scene
		auto light = make_shared<directional_light>();
		light->data.ambient_intensity = ambient_intensity;
		light->data.colour = light_colour;
		light->data.direction = light_direction;
		light->build();

		// Set light for objects
		object[0]->mat->set_uniform_value("directional_light", light);
		plane->mat->set_uniform_value("directional_light", light);

		// Load texture
		auto tex = texture_loader::load("Checkered.png");

		// Set texture on materials
		object[0]->mat->set_texture("tex", tex);
		plane->mat->set_texture("tex", tex);

		// Build materials 
		if (!object[0]->mat->build()) {
			return false;
		}
		if (!plane->mat->build()) {
			return false;
		}

		object[0]->trans.translate(vec3(0.0, 2.0, 0.0));
		plane->trans.translate(vec3(0.0, -2.0, 0.0));

	return true;

} // load_content()


bool load_camera() {
	// Initialize the camera
	cam = make_shared<free_camera>();

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
	cam->set_position(vec3(0.0, 0.0, 20.0));

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

	if (!load_camera()) {
		return -1;
	}

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