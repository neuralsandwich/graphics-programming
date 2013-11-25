#include "Prop.h"

/** Prop : Empty Constuctor
 *
 * Allows Prop to be created and initialised at a later point
 */
Prop::Prop(void) { }

/** ~Prop : Destructs the prop
 *
 * Destroys the object.
 */
Prop::~Prop(void)
{
	models.erase(models.begin(), models.end());
} // ~Prop()

/** get_mesh() : Returns Prop model
 *
 * Returns the data structure the represents the model
 */
mesh Prop::get_mesh(int i)
{
	return models.at(i);
} // get_mesh()

void Prop::add_mesh(mesh* mesh)
{
	models.push_back(*mesh);
}

/**
 *
 *
 */
string Prop::get_path()
{
	return path;
}
