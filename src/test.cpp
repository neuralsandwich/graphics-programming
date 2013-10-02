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

// Keep track of current mode
int MODE = 0;

// Keep track of camera orientation
float cameraOrientation = 0.0f;
// Keep track of cube position
vec3 position(0.0f, 0.0f, 0.0f);
// Keep track of cube rotation
vec3 rotation(0.0f, 0.0f, 0.0f);
// Keep track of cube scale
vec3 cube_scale(1.0f, 1.0f, 1.0f);


array<float, 24> vertices =
    {
     -1.0f, 1.0f, 1.0f,       // 0
     1.0f, 1.0f, 1.0f,        // 1
     1.0f, -1.0f, 1.0f,       // 2
     -1.0f, -1.0f, 1.0f,      // 3
     1.0f, 1.0f, -1.0f,       // 4
     -1.0f, 1.0f, -1.0f,      // 5
     -1.0f, -1.0f, -1.0f,     // 6
     1.0f, -1.0f, -1.0f       // 7
    };


array<unsigned int, 36> indices =
    {
     // Side 1
     0, 1, 3,
     1, 2, 3,
     // Side 2
     1, 4, 2,
     4, 7, 2,
     // Side 3
     4, 5, 7,
     5, 6, 7,
     // Side 4
     5, 0, 6,
     0, 3, 6,
     // Side 5
     5, 4, 0,
     4, 1, 0,
     // Side 6
     3, 2, 6,
     2, 7, 6
    };


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
  // Enable vertex arrays
  glEnableClientState(GL_VERTEX_ARRAY);

  return true;
} // initialise

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
 * userScale
 *
 * Increases and decreases the scale of the object.
 */
void userScale(double deltaTime) {

  if (glfwGetKey(window, GLFW_KEY_UP)) {
    cube_scale.z -= (deltaTime * pi<float>());
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN)) {
    cube_scale.z += (deltaTime * pi<float>());
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
    cube_scale.x += (deltaTime * pi<float>());
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT)) {
    cube_scale.x -= (deltaTime * pi<float>());
  }
  if (glfwGetKey(window, 'W')) {
    cube_scale.y += (deltaTime * pi<float>());
  }
  if (glfwGetKey(window, 'S')) {
    cube_scale.y -= (deltaTime * pi<float>());
  }

} // userScale


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

  switch (MODE) {
    case 0:
      userTranslation(deltaTime);
      break;
    case 1:
      userRotation(deltaTime);
      break;
    case 2:
      userScale(deltaTime);
      break;
    default:
      break;
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

  auto model = rotate(mat4(1.0f), degrees(rotation.y), vec3(0.0f, 1.0f, 0.0f));
  model = rotate(model, degrees(rotation.x), vec3(1.0f, 0.0f, 0.0f));
  model = rotate(model, degrees(rotation.z), vec3(0.0f, 0.0f, 1.0f));
  model = scale(model, cube_scale);
  model = translate(model, position);


  // Set matrix mode
  glMatrixMode(GL_MODELVIEW);
  // Load view matrix
  glLoadMatrixf(value_ptr(view * model));

  // Point to the vertex data - vec3 of float.  Start at index 0
  glVertexPointer(3, GL_FLOAT, 0, &vertices);
  // Set the colour
  glColor3f(1.0f, 0.0f, 0.0f);
  // Draw the triangles using the index data
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &indices);

  // Render a cube
  glBegin(GL_QUADS);


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
