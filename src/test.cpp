// Test.cpp
// Sean Jones

#include "../renderframework/render_framework.h"
#include <glm/gtx/constants.hpp>

// For Debug
#include <iostream>


using namespace glm;
using namespace render_framework;


int main(void)
{
  // Initialise the renderer
  if (!renderer::get_instance().initialise()) {
    return -1;
  }

  // Set the clear colour to cyan (close to sky blue)
  glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

  // Set the projection matrix
  // First get the aspect ration (width/height)
  float aspect = (float)renderer::get_instance().get_screen_width()
              / (float)renderer::get_instance().get_screen_height();
  // Use this to create the projection matrix
  auto projection = perspective(degrees(quarter_pi<float>()), //FOV
                                aspect,
                                2.414f,
                                10000.0f);
  renderer::get_instance().set_view(projection);

  // Set the view matrix
  auto view = lookAt(vec3(20.0f, 20.0f, 20.0f), // Camera position
                     vec3(0.0f, 0.0f, 0.0f),    // Target
                     vec3(0.0f, 1.0f, 0.0f));   // Up direction (orientation)

  // Main render loop
  while (renderer::get_instance().is_running()) {
    // Check if running
    if (renderer::get_instance().begin_render()) {
      //end the render
      renderer::get_instance().end_render();
    }
  }

} // main
