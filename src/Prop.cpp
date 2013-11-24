#include "Prop.h"

/** Prop : Empty Constuctor
 *
 * Allows Prop to be created and initialised at a later point
 */
Prop::Prop(void) { }

/** Prop : Takes a mesh and creates the prop
 *
 * The prop is created with a model mesh
 */
Prop::Prop(shared_ptr<mesh> mesh)
{
	*model = *mesh;
} // Prop()

/** ~Prop : Destructs the prop
 *
 * Destroys the object.
 */
Prop::~Prop(void)
{
	model->~mesh();
} // ~Prop()

/** get_mesh() : Returns Prop model
 *
 * Returns the data structure the represents the model
 */
mesh Prop::get_mesh()
{
	return *model;
} // get_mesh()

/** set_mesh() : Sets Prop model
 *
 * Takes a mesh and set Prop model to those values
 */
void Prop::set_mesh(mesh mesh)
{
	*model = mesh;
} // set_mesh()