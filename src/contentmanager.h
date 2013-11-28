#include <vector>
#include <iostream>
#include <GLM\glm.hpp>

#include "tiny_obj_loader.h"
#include "CSVparser.hpp"
#include "cameramanager.h"
#include "scenemanager.h"
#include "Prop.h"
#include "Sputnik.h"
#include "Earth.h"
#include "Moon.h"

#pragma once

using namespace std;
using namespace glm;
using namespace render_framework;

class ContentManager {
public:

	shared_ptr<skybox> sky_box;

	shared_ptr<post_process> post;

	shared_ptr<render_pass> normal;

	shared_ptr<render_pass> grey;

	shared_ptr<render_pass> sin;

	shared_ptr<render_pass> pixelate;

	// Destructor for CameraManager
	~ContentManager() { shutdown(); };

	// Gets singleton instance o
	static ContentManager& get_instance()
	{
		static ContentManager instance;

		return instance;
	}

	// Gets the current running state of the renderer
	bool is_running() const { return _running; }

	// Initialise the CameraManager
	bool initialize();

	// Update cameras
	void update(float deltaTime);

	// Register object with scene manager for rendering
	void register_prop(Prop* prop);

	// Unregister object with scene manager
	void unregister_prop(Prop* prop);

	// Get object at index
	Prop* get_prop_at(int index);

	// Get propList's size
	int prop_list_size();

	// Load Content
	bool load_props();

	// Load Content
	bool load_skybox();

	bool load_frame_buffer();

	// Load model
	bool load_model(Prop* prop, string modelPath);

	// load vertices for model
	void load_vertices(tinyobj::shape_t * shape, mesh * model);

	// load normals for model
	void load_normals(tinyobj::shape_t * shape, mesh * model);

	// load texture coordinates for model
	void load_texcoords(tinyobj::shape_t * shape, mesh * model);

	// load indices for model
	void load_indices(tinyobj::shape_t * shape, mesh * model);

	// load shader information for model
	void load_shader_data(tinyobj::shape_t * shape, mesh * model);

private:

	// Private flag for current status of the manager
	bool _running;

	// Private collection of Props
	vector<Prop*> prop_list;

	// Path to scene prop list
	string path;

	Sputnik sputnik;

	Earth earth;

	Moon moon;

	// Private constructor (This CameraManager is a singleton)
	ContentManager() {};

	// Private copy constructor
	ContentManager(const ContentManager&);

	// Private assignment operator
	void operator=(ContentManager&);

	void shutdown();
};