#include "Moon.h"

const double Moon::mass = 7.3477e22;

Moon::Moon(void)
{
	name = "Moon";
	path = "Moon.obj";
	vert = "Moon.vert";
	frag = "Moon.frag";
	//position = vec3(-384399e3, 0.0, -384399e3);
	position = vec3(-384399.0, 0.0, -384399.0);
	//velocity = vec3(29.78e3, 0.0, 0.0);
	velocity = vec3(0.0, 0.0, 0.0);
	rotation = vec3(0.0, 0.0, 0.0);
	scale    = vec3(60.0, 60.0, 60.0);
}

Moon::~Moon(void)
{
}

void Moon::update(void)
{
}