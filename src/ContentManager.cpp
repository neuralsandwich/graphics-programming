#include "contentmanager.h"

#include <iostream>
#include <GLM\glm.hpp>

#include "objloader.hpp"
#include "CSVparser.hpp"

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


bool ContentManager::loadPropList(string path) {
	printf("Loading Scene from %s.\n", path);

	vector<string> modelPath;
	vector<vec3> modelPosition;

	try {
		csv::Parser file = csv::Parser(path);

		int i;
		for (i=0; i < file.rowCount(); ++i) {
			modelPath.push_back(file[i][0]);
			modelPosition.push_back(vec3(stof(file[i][1]), stof(file[i][2]), stof(file[i][3])));
		}

	} catch (csv::Error &e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	loadModel(&modelPath, &modelPosition);

	return true;
}


void ContentManager::loadModel(vector<string> * modelPath, vector<vec3> * modelPosition) {



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

// Get propList's size
int ContentManager::propListSize() {
	return propList.size();
}


void ContentManager::shutdown() {

	_running = false;
}