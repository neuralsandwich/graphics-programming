#include "Prop.h"

/** Prop : Empty Constuctor
 *
 * Allows Prop to be created and initialised at a later point
 */
Prop::Prop(void) { }

/** Prop : Creates Prop with name and model mesh
 *
 * The prop is created with a model mesh and a Prop identifier
 */
Prop::Prop(string string, mesh mesh)
{
	name = string;
	models.push_back(mesh);
} // Prop()

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