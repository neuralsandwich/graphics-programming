#include "Sol.h"


Sol::Sol(void)
{
	name = "Sol";
	path = "Sol.obj";
	vert = "Sol.vert";
	frag = "Sol.frag";
	position = vec3(-0.9e8, 0.0, 0.9e8);
	//position = vec3(0.0, 0.0, 0.0);
	velocity = vec3(0.0,  0.0,  0.0);
	rotation = vec3(0.0,  0.0,  0.0);
	scale    = vec3(60.0, 60.0, 60.0);
}

Sol::~Sol(void)
{
}

void Sol::update()
{
	rotate();
}

void Sol::rotate()
{
	models.at(0).trans.rotate(vec3(0.0, pi<float>(), 0.0) * (float) 5.0e-5);
}