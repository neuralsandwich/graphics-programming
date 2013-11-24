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
	Prop(string string, mesh models);
	// Destructors
	~Prop(void);

	// Functions
	// Update Prop
	virtual void update(void) = 0;
	// Get Prop model
	mesh get_mesh(int i);

protected:
	// name
	string name;
	// Prop model
	vector<mesh> models;
	// Prop effects
	vector<effect> vert;
	// Position
	vec3 position;
	// Rotation
	vec3 rotation;
};