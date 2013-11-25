#include "Sputnik.h"

double const Sputnik::mass = 84.06;

Sputnik::Sputnik(void)
{
	name = "Sputnik";
	position = vec3(228e3, 0.0, 0.0);
	velocity = vec3((float)8e3, (float) 0.0, (float) 0.0);
}


Sputnik::~Sputnik(void)
{
}

void Sputnik::update(void)
{
}