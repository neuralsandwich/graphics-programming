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
glm::vec3 position(0.0f, 0.0f, 0.0f);

bool initialise()
{
  // Set Color to cyan
  glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

  return true;
} // initialise

//updates the application
void update(double deltaTime)
{
  // Check if escape pressed or window is closed
  running = !glfwGetKey(window, GLFW_KEY_ESCAPE) &&
    !glfwWindowShouldClose(window);

  // Move the quad when arrow keys are pressed
  if (glfwGetKey(window, GLFW_KEY_RIGHT)){
    position += glm::vec3(1.0f, 0.0f, 0.0f) * float(deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT)){
    position -= glm::vec3(1.0f, 0.0f, 0.0f) * float(deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_UP)){
    position += glm::vec3(0.0f, 1.0f, 0.0f) * float(deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN)){
    position -= glm::vec3(0.0f, 1.0f, 0.0f) * float(deltaTime);
  }
} // update

//renders the application
void render()
{

  // Create model matrix
  auto model = glm::translate(glm::mat4(1.0f), position);

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
