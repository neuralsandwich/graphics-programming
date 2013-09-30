// Test.cpp
// Sean Jones

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <chrono>

using namespace std::chrono;

GLFWwindow* window;

bool running = true;

// Value to keep track of current orientation on axis
float orientation = 0.0f;

bool initialise()
{
  // Set Color to cyan
  glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
  //Enable face culling
  glEnable(GL_CULL_FACE);
  return true;
} // initialise

//updates the application
void update(double deltaTime)
{
  // Check if escape pressed or window is closed
  running = !glfwGetKey(window, GLFW_KEY_ESCAPE) &&
    !glfwWindowShouldClose(window);
} // update

//renders the application
void render()
{
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT);

  //Set the colour
  glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

  //Render a Triangel
  glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);

  glEnd();

  // Swap front and back buffers
  glfwSwapBuffers(window);
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
