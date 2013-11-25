/** Prop : Class for prop, contains mesh and functions
 *
 * Model data is held in a mesh and all other prop specific datais also
 * included.  All opertations for the model are included. These operations
 * should be called in the update method.
 */

#include <render_framework\render_framework.h>
#include <GLM\glm.hpp>

#pragma once

using namespace std;
using namespace glm;
using namespace render_framework;

class Prop
{
public:
	// Constructors
	Prop(void);

	// Destructors
	~Prop(void);

	// Functions
	// Update Prop
	virtual void update(void) = 0;
	
	// Get Prop model
	mesh get_mesh(int i);
	
	// Set Prop model
	void add_mesh(mesh* mesh);
	
	// Get path
	string get_path();

	// Get vertex shader path
	string get_vert_path();

	// Get fragment shader path
	string get_frag_path();

	// Get Prop position
	vec3 get_position();

	// Get Prop rotation
	vec3 get_rotation();

protected:
	// name
	string name;
	// Prop model
	vector<mesh> models;
	// Position
	vec3 position;
	// Rotation
	vec3 rotation;
	// Path to .OBJ file
	string path;
	// Path to vertex shader
	string vert;
	// Path to fragment shader
	string frag;
};