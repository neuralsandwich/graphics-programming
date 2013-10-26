#include "contentmanager.h"

#include <iostream>
#include <GLM\glm.hpp>

#include "tiny_obj_loader.h"
#include "CSVparser.hpp"

using namespace std;
using namespace glm;

bool ContentManager::initialize() {

	path = "proplist.csv";

	if (!loadPropList(path)) {
		printf("Failed to read prop list, cannot render scene.\n");
		return false;
	}

	_running = true;

	return true;
}

void ContentManager::update(float deltaTime) {}


bool ContentManager::loadPropList(string path) {
	printf("Loading Scene from %s.\n", path.c_str());

	vector<string> modelPath;
	vector<vec3> modelPosition;

	try {
		csv::Parser file = csv::Parser(path);

		int i;
		for (i=0; i < file.rowCount(); ++i) {
			modelPath.push_back(file[i][0]);
			modelPosition.push_back(vec3(stof(file[i][1]), stof(file[i][2]), stof(file[i][3])));
		}

		for (i=0; i < modelPath.size(); ++i) {
			if (!loadModel(modelPath.at(i), modelPosition.at(i))) {
				return false;
			}
		}

	} catch (csv::Error &e) {
		std::cerr << e.what() << std::endl;
		return false;
	}



	return true;
}


bool ContentManager::loadModel(string modelPath, vec3 modelPosition) {
	mesh model;
	std::vector<tinyobj::shape_t> shapes;

	std::string err = tinyobj::LoadObj(shapes, modelPath.c_str());

	std::cout << "# of shapes : " << shapes.size() << std::endl;

	if (!err.empty()) {
		std::cerr << err << std::endl;
		return false;
	}


	return true;
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