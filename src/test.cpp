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

// Number of points to generate
const int num_points = 50000;
// Points generated
vector<vec2> points;


bool initialise()
{
	// Set background to white.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);

	// Enable face culling
	glEnable(GL_CULL_FACE);

	// The three points we randomly select from
	vec2 v[3] =
	{
			vec2(-1.0f, -1.0f),
			vec2(0.0f, 1.0f),
			vec2(1.0f, -1.0f)
	};

	// Add starting point
	points.push_back(vec2(0.25f, 0.5f));

	// Create a random engine
	default_random_engine re;

	// Create a distribution. 3 points in array, so get 0, 1 or 2.
	uniform_int_distribution<int> dist(0,2);


	int k;
	for(k=0; k <5000; k++)
	{
		float x,y;

		int r = dist(re);

		/* compute point halfway between vertex and old point */
		points.push_back(vec2(
				(points.at(points.size()-1).x + v[r].x)/2.0,
				(points.at(points.size()-1).y + v[r].y)/2.0));
	}

	return true;
} // initialise

//updates the application
void update(double deltaTime)
{


} // update

//renders the application
void render()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
	// Set Colour to black
	glColor3f(0.0f, 0.0f, 0.0f);

	//Render a Triangle
	glBegin(GL_POINTS);
	for (vec2& point : points) {
		glVertex2fv(value_ptr(point));
	}
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
