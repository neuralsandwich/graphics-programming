// Test.cpp
// Sean Jones

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/core/type_vec3.hpp>
#include <vector>
#include <random>
#include <chrono>
#include <array>
// For Debug
#include <iostream>


using namespace glm;
using namespace std;
using namespace std::chrono;

GLFWwindow* window;

bool running = true;


// Vector containing vector data
vector<vec2> vertices;


/*
 * triangle()
 *
 * Helper function to create a triangle
 */
void triangle(const vec2& a, const vec2& b, const vec2& c)
{
  // Push the vertices onto the vector
  vertices.push_back(a);
  vertices.push_back(b);
  vertices.push_back(c);
} // Triangle


void divide_triangle(const vec2& a, const vec2& b, const vec2& c, int count)
{
}


/*
 * Initialise()
 *
 * Initialises the application
 */
bool initialise()
{
  // Set background to cyan.
  glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
  // Enable face culling
  glEnable(GL_CULL_FACE);
  // Enable depth testing
  glEnable(GL_DEPTH_TEST);
  // Enable vertex arrays
  glEnableClientState(GL_VERTEX_ARRAY);

  // Starting vertices - edge of the screen
  array<vec2, 3> v =
      {
       vec2(1.0f, -1.0f),
       vec2(0.0f, 1.0f),
       vec2(-1.0f, -1.0f)
      };

  // Divide the triangle first - you will need to modify this
  divide_triangle(v[0], v[1], v[2], 0);

  return true;
} // initialise


/*
 * update()
 *
 * Updates the application state
 */
void update(double deltaTime) {

  // Check if escape pressed or window is closed
  running = !glfwGetKey(window, GLFW_KEY_ESCAPE) &&
      !glfwWindowShouldClose(window);

} // update


/*
 * render()
 *
 * renders the application
 */
void render()
{
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Point to the internal array of the vector
  glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);

  // Set the colour
  glColor3f(1.0f, 0.0f, 0.0f);

  // Draw the arrays - start at 0 and have n vertices
  glDrawArrays(GL_TRIANGLES, 0, vertices.size());

  // Swap front and back buffers
  glfwSwapBuffers(window);

  // Set transform matrix to identity (no transform)
  glLoadIdentity();

} // render

int main(void)
{
  /* Initialise the library */
  if (!glfwInit())
  {
    return -1;
  }

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Sierpinski", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  /* Set the function for the key callback */

  //initialise the window
  if (!initialise())
  {
    glfwTerminate();
    return -1;
  }

  // Monitor the elapsed time per frame
  auto currentTimeStamp = system_clock::now();
  auto prevTimeStamp = system_clock::now();


  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    // Get current time
    currentTimeStamp = system_clock::now();
    // Calculate elapsed time
    auto elapsed = duration_cast<milliseconds>(currentTimeStamp
                                               - prevTimeStamp);
    //Convert to fractions of a second
    auto seconds = double(elapsed.count()) / 1000.0;

    // Update Application
    update(seconds);
    //Render scene
    render();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

    // set the previous time stamp to current time stamp
    prevTimeStamp = currentTimeStamp;
  } // Main Loop

  glfwTerminate();
  return 0;
} // main
