#include "Earth.h"

const double Earth::mass = 5.9721986e24;

Earth::Earth(void)
{
	name = "Earth";
	position = vec3(1.52097701e8, 0, 0);
	velocity = vec3((float) 29.78e3, (float) 0, (float) 0);
}


Earth::~Earth(void)
{
}

void Earth::update(void)
{
}

void Earth::update_clouds(void)
{
}