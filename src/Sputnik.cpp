#include "Sputnik.h"

double const Sputnik::mass = 84.06;

Sputnik::Sputnik(void)
{
	name = "Sputnik";
	path = "Sputnik.obj";
	vert = "Sputnik.vert";
	frag = "Sputnik.frag";

	//position = vec3(228e3, 0.0, 0.0);
	position = vec3(0.0, 0.0, 6939.0);
	//velocity = vec3((float)8e3, (float) 0.0, (float) 0.0);
	velocity = vec3(0.0, 0.0, 0.0);
	rotation = vec3(0.0,0.0,-1.5707963267);
	scale = vec3(1.0, 1.0, 1.0);
}


Sputnik::~Sputnik(void)
{
}

void Sputnik::update(void)
{
}