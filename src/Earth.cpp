#include "Earth.h"

const double Earth::mass = 5.9721986e24;

Earth::Earth(void)
{
	name = "Earth";
	path = "Earth.obj";
	vert = "Earth.vert";
	frag = "Earth.frag";
	//position = vec3(1.52097701e8, 0, 0);
	position = vec3(0.0,  0.0,  0.0);
	//velocity = vec3((float) 29.78e3, (float) 0, (float) 0);
	velocity = vec3(0.0,  0.0,  0.0);
	rotation = vec3(0.0,  0.0,  0.0);
	scale    = vec3(60.0, 60.0, 60.0);
}


Earth::~Earth(void)
{
}

void Earth::update(void)
{
	update_clouds();
}

void Earth::update_clouds(void)
{
	models.at(clouds).trans.rotate(vec3(0.0, pi<float>(), 0.0) * (float) 0.00005);
}