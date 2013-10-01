// Test.cpp
// Sean Jones

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtx/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/core/type_vec3.hpp>

using namespace std::chrono;

GLFWwindow* window;

bool running = true;

// Value to keep track of current orientation on axis
float orientation = 0.0f;
// Keep track of position
glm::vec3 position(0.0f, 0.0f, 0.0f);
// Keep track of scale
float scale = 1.0f;

// Keep track of current mode
bool TRANSLATIONMODE = true;

bool initialise()
{
  // Set Color to cyan
  glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

  return true;
} // initialise


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    if (TRANSLATIONMODE == true) {
      TRANSLATIONMODE = false;
    } else {
      TRANSLATIONMODE = true;
    }

  }
}

void userRotation(double deltaTime) {

  if (glfwGetKey(window, GLFW_KEY_RIGHT)){
    orientation += (deltaTime * glm::pi<float>());
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT)){
    orientation -= (deltaTime * glm::pi<float>());
  }

}

/*
 * userScale
 *
 * Increases and decreases the scale of the object.
 */
void userScale(double deltaTime) {
  if (glfwGetKey(window, GLFW_KEY_UP)){
    scale += 1.0f * float(deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN)){
    scale -= 1.0f * float(deltaTime);
  }

}

/*
 * userTranslation
 *
 * moves the object around inside the window using the keyboard arrow keys.
 */
void userTranslation(double deltaTime) {
  // Move the quad when arrow keys are pressed
  if (glfwGetKey(window, GLFW_KEY_RIGHT)){
    if (position.x < (1 - (scale/2))) {
      position += glm::vec3(1.0f, 0.0f, 0.0f) * float(deltaTime);
    }
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT)){
    if (position.x > (-1.0 + (scale/2))) {
      position -= glm::vec3(1.0f, 0.0f, 0.0f) * float(deltaTime);
    }
  }
  if (glfwGetKey(window, GLFW_KEY_UP)){
    if (position.y < (1.0 - (scale/2))) {
      position += glm::vec3(0.0f, 1.0f, 0.0f) * float(deltaTime);
    }
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN)){
    if (position.y > (-1.0 + (scale/2))) {
      position -= glm::vec3(0.0f, 1.0f, 0.0f) * float(deltaTime);
    }
  }

} // userTranslation

//updates the application
void update(double deltaTime)
{
  // Check if escape pressed or window is closed
  running = !glfwGetKey(window, GLFW_KEY_ESCAPE) &&
    !glfwWindowShouldClose(window);

  if (TRANSLATIONMODE) {
    userTranslation(deltaTime);
  } else {
    userScale(deltaTime);
    userRotation(deltaTime);
  }

} // update

//renders the application
void render()
{

  // Create model matrix
  auto model = glm::translate(glm::mat4(1.0f), position);
  // Scale the triangle
  model *= glm::scale(scale, scale, scale);
  // Create rotation transform. Use Z-axis
  model *= glm::rotate(glm::mat4(10.f), glm::degrees(orientation),
                       glm::vec3(0.0f, 0.0f, 1.0f));

  // Set matrix mode
  glMatrixMode(GL_MODELVIEW);

  // Load model matrix
  glLoadMatrixf(glm::value_ptr(model));

  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT);

  //Set the colour
  glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

  //Render a Triangel
  glBegin(GL_QUADS);

    glVertex3f(0.5f, 0.5f, 0.0f);
    glVertex3f(-0.5f, 0.5f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);

  glEnd();

  // Swap front and back buffers
  glfwSwapBuffers(window);

  // Set transform matrix to identity (no transform)
  glLoadIdentity();

} // render

int main(void)
{
    /* Initialize the library */
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
