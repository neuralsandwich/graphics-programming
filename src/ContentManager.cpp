#include "contentmanager.h"

#include <iostream>
#include <GLM\glm.hpp>

#include "objloader.hpp"

using namespace std;
using namespace glm;

bool ContentManager::initialize() {

	_running = true;
	
	mesh box = mesh();
	box.geom = geometry_builder::create_box();
	box.trans.translate(vec3(0.0, 2.0, 0.0));

	registerProp(box);

	return true;
}

void ContentManager::update(float deltaTime) {

}

/*
* Register object with scene manager for rendering
*/
void ContentManager::registerProp(mesh object)
{
	printf("propList has %d membersi.\n", propList.size());
	printf("Added Prop.\n");
	propList.push_back(object);
	printf("propList now has %d members.\n", propList.size());
}

/*
* Unregister object with scene manager
*/
void ContentManager::unregisterProp(mesh object)
{
	printf("Removed Prop.\n");
	propList.push_back(object);
}


// Get object at index
mesh ContentManager::getPropAt(int index) {

	printf("Getting Prop at index: %d.\n", index);
	printf("propList is %d long.\n", propList.size());
	mesh result = propList.at(index);
	mesh result1 = result;
	return result;
}


void ContentManager::shutdown() {
	
	_running = false;
}