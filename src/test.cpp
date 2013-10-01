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

// For Debug
#include <iostream>


using namespace glm;
using namespace std;
using namespace std::chrono;

GLFWwindow* window;

bool running = true;

float cameraOrientation = 0.0f;

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
  // Create projection matrix
  auto projection = perspective(degrees(quarter_pi<float>()),
                                800.0f / 600.0f,
                                2.414f,
                                10000.0f);
  // Set matrix mode to projection
  glMatrixMode(GL_PROJECTION);
  // Load projection matrix
  glLoadMatrixf(value_ptr(projection));
  // Set matrix mode back to model view
  glMatrixMode(GL_MODELVIEW);
  // Enable depth testing
  glEnable(GL_DEPTH_TEST);

  return true;
} // initialise


/*
 * update()
 *
 * Updates the application state
 */
void update(double deltaTime) {

  cameraOrientation += (deltaTime * pi<float>());

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
  // Create view matrix
  auto view = lookAt(vec3(10.0f, 10.0f, 10.0f),
                     vec3(0.0f, 0.0f, 0.0f),
                     vec3(0.0f, 1.0f, 0.0f));

  view *= rotate(mat4(10.f),
                      degrees(cameraOrientation),
                      vec3(1.0f, 1.0f, 1.0f));

  // Set matrix mode
  glMatrixMode(GL_MODELVIEW);
  // Load view matrix
  glLoadMatrixf(value_ptr(view));

  // Render a cube
  glBegin(GL_QUADS);
    // Face 1
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    // Face 2
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    // Face 3
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    // Face 4
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    // Face 5
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    // Face 6
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
  glEnd();
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
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

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
