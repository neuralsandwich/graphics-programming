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

// Keep track of current mode
bool TRANSLATIONMODE = true;

// Keep track of camera orientation
float cameraOrientation = 0.0f;
// Keep track of cube position
vec3 position(0.0f, 0.0f, 0.0f);
// Keep track of cube rotation
vec3 rotation(0.0f, 0.0f, 0.0f);

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
 * key_callback
 *
 * used for identifying key presses
 */
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    if (TRANSLATIONMODE == true) {
      TRANSLATIONMODE = false;
    } else {
      TRANSLATIONMODE = true;
    }

  }
} // key_callback


/*
 * userRation
 *
 * rotates the object
 */
void userRotation(double deltaTime) {

  if (glfwGetKey(window, GLFW_KEY_UP)) {
    rotation.z -= (deltaTime * pi<float>());
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN)) {
    rotation.z += (deltaTime * pi<float>());
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
    rotation.x += (deltaTime * pi<float>());
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT)) {
    rotation.x -= (deltaTime * pi<float>());
  }
  if (glfwGetKey(window, 'W')) {
    rotation.y += (deltaTime * pi<float>());
  }
  if (glfwGetKey(window, 'S')) {
    rotation.y -= (deltaTime * pi<float>());
  }

} // userRoation


/*
 * userTranslation
 *
 * moves the object around inside the window using the keyboard arrow keys.
 */
void userTranslation(double deltaTime) {
  // Move the quad when arrow keys are pressed
  if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
    position.x += 1.0f * deltaTime;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT)) {
    position.x -= 1.0f * deltaTime;
  }
  if (glfwGetKey(window, GLFW_KEY_UP)) {
    position.z += 1.0f * deltaTime;
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN)) {
    position.z -= 1.0f * deltaTime;
  }
  if (glfwGetKey(window, 'W')) {
    position.y += 1.0f * deltaTime;
  }
  if (glfwGetKey(window, 'S')) {
    position.y -= 1.0f * deltaTime;
  }
}


/*
 * update()
 *
 * Updates the application state
 */
void update(double deltaTime) {

  // Check if escape pressed of window is closed
  running = !glfwGetKey(window, GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(window);

  // Check if escape pressed or window is closed
  running = !glfwGetKey(window, GLFW_KEY_ESCAPE) &&
    !glfwWindowShouldClose(window);

  if (TRANSLATIONMODE) {
    userTranslation(deltaTime);
  } else {
    userRotation(deltaTime);
  }
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

  auto model = translate(mat4(1.0f), position);
  model = rotate(model, degrees(rotation.y), vec3(0.0f, 1.0f, 0.0f));
  model = rotate(model, degrees(rotation.x), vec3(1.0f, 0.0f, 0.0f));
  model = rotate(model, degrees(rotation.z), vec3(0.0f, 0.0f, 1.0f));

  // Set matrix mode
  glMatrixMode(GL_MODELVIEW);
  // Load view matrix
  glLoadMatrixf(value_ptr(view * model));

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
  /* Set the function for the key callback */
  glfwSetKeyCallback(window, key_callback);

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
