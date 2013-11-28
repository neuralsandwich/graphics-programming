#include "Prop.h"

/* Prop : Empty Constuctor
 *
 * Allows Prop to be created and initialised at a later point
 */
Prop::Prop(void) { }

/* ~Prop : Destructs the prop
 *
 * Destroys the object.
 */
Prop::~Prop(void)
{
	models.erase(models.begin(), models.end());
} // ~Prop()

/* get_mesh : Returns Prop model
 *
 * Returns the data structure the represents the model
 */
mesh Prop::get_mesh(int i)
{
	return models.at(i);
} // get_mesh()

/* add_mesh : Adds mesh to prop
 *
 * Takes a ptr to a mesh and adds it to the vector of meshes for model
 */
void Prop::add_mesh(mesh* mesh)
{
	models.push_back(*mesh);
} // add_mesh()

/* get_path : Returns path of the .OBJ file
 *
 * returns a string containing the path for props .OBJ file
 */
string Prop::get_path()
{
	return path;
} // get_path()

/* get_vert_path : Returns path to the vertex shader
 *
 * returns a string containing the path for props vertex shader
 */
string Prop::get_vert_path()
{
	return vert;
} // get_vert_path()

/* get_frag_path : Returns path to the vertex shader
 *
 * returns a string containing the path for props vertex shader
 */
string Prop::get_frag_path()
{
	return frag;
} // get_frag_path()

/* get_position : Returns Prop position
 * 
 * Returns vec3 position
 */
vec3 Prop::get_position()
{
	return position;
} // get_position()

/* get_rotation : Get Prop rotation
 *
 * Returns vec3 rotation
 */
vec3 Prop::get_rotation()
{
	return rotation;
} // get_rotation()

/* get_scale : Get Prop scale
 *
 * Returns vec3 scale
 */
vec3 Prop::get_scale()
{
	return scale;
} // get_scale()

/* mesh_size : number of mesh for prop
 *
 * Returns and integer for the number of meshes in prop
 */
int Prop::mesh_size()
{
	return models.size();
}

string Prop::get_name()
{
	return name;
}