/** Prop.cpp : Class for prop, contains mesh and functions
 *
 * Model data is held in a mesh and all other prop specific datais also
 * included.  All opertations for the model are included. These operations
 * should be called in the update method.
 */

#include <render_framework\render_framework.h>

#pragma once

using namespace std;
using namespace render_framework;

class Prop
{
public:
	// Constructors
	Prop(void);
	Prop(shared_ptr<mesh> mesh);
	// Destructors
	~Prop(void);

	// Functions
	// Update Prop
	virtual void update(void) = 0;
	// Get Prop model
	mesh get_mesh();
	// Set Prop model
	void set_mesh(mesh mesh);


protected:
	// Prop model
	shared_ptr<mesh> model;
};

