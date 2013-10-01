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

// Value to keep track of current orientation on axis
float objOrientation = 0.0f;
// Keep track of position
glm::vec3 objPosition(0.0f, 0.0f, 0.0f);
// Keep track of scale
float objScale = 1.0f;

// Keep track of current mode
bool TRANSLATIONMODE = true;

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

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		if (TRANSLATIONMODE == true) {
			TRANSLATIONMODE = false;
		} else {
			TRANSLATIONMODE = true;
		}

	}
} // Key_callback

void userRotation(double deltaTime) {

	if (glfwGetKey(window, GLFW_KEY_RIGHT)){
		objOrientation += (deltaTime * pi<float>());
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT)){
		objOrientation -= (deltaTime * pi<float>());
	}

}

/*
 * userScale
 *
 * Increases and decreases the scale of the object.
 */
void userScale(double deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_UP)){
		objScale += 1.0f * float(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)){
		objScale -= 1.0f * float(deltaTime);
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
		if (objPosition.x < (1 - (objScale/2))) {
			objPosition += vec3(1.0f, 0.0f, 0.0f) * float(deltaTime);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT)){
		if (objPosition.x > (-1.0 + (objScale/2))) {
			objPosition -= vec3(1.0f, 0.0f, 0.0f) * float(deltaTime);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_UP)){
		if (objPosition.y < (1.0 - (objScale/2))) {
			objPosition += vec3(0.0f, 1.0f, 0.0f) * float(deltaTime);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)){
		if (objPosition.y > (-1.0 + (objScale/2))) {
			objPosition -= vec3(0.0f, 1.0f, 0.0f) * float(deltaTime);
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
	auto model = translate(mat4(1.0f), objPosition);
	// Scale the triangle
	model *= scale(objScale, objScale, objScale);
	// Create rotation transform. Use Z-axis
	model *= rotate(mat4(10.f),
					degrees(objOrientation),
			        vec3(0.0f, 0.0f, 1.0f));

	// Set matrix mode
	glMatrixMode(GL_MODELVIEW);
	// Load model matrix
	glLoadMatrixf(value_ptr(model));

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
