#include "contentmanager.h"

/*
* initialize()
*
* Initializes the ContentManager.  Models described in the external proplist
* are loaded into the ContentManagers proplist
*/
bool ContentManager::initialize() {
	cout << "## Initializing ContentManager ##" << endl;

	path = "proplist.csv";

	if (!load_prop_list(path)) {
		printf("Failed to read prop list, cannot render scene.\n");
		return false;
	}

	_running = true;

	cout << "## Initialized ContentManager ##" << endl;
	return true;
}

/*
* shutdown
*
* stops the ContentManager
*/
void ContentManager::shutdown() {
	_running = false;
} // shutdown()

/*
* update()
*
* Updates objects in the proplist
*/
void ContentManager::update(float deltaTime) {
	//TODO - Needs implemented
} // update(float deltaTime)

/*
* prop_list_size
*
* returns the size of prop_list
*/
int ContentManager::prop_list_size() {
	return prop_list.size();
} // prop_list_size()

/*
* get_prop_at
* Parameter (int index) - index of prop
*
* Gets the prop at the index provided from
* prop_list
*/
mesh ContentManager::get_prop_at(int index) {
	mesh result = prop_list.at(index);
	mesh result1 = result;
	return result;
} // get_prop_at(int index)

/*
* register_prop()
*
* Register object with scene manager for rendering
*/
void ContentManager::register_prop(mesh mesh)
{
	prop_list.push_back(mesh);
} // register_prop(mesh mesh)

/*
*  unregister_prop()
*
* Unregister object with scene manager
*/
void ContentManager::unregister_prop(mesh mesh)
{
	prop_list.push_back(mesh);
} // unregister_prop(mesh object)

/*
* load_prop_list()
* Parameter string path - Path for external proplist
*
* Loads models from external proplist in to the ContentManagers
* interal proplist
*/
bool ContentManager::load_prop_list(string path) {
	vector<string> modelPath;
	vector<vec3> modelPosition;
	vector<vec3> modelRotation;
	vector<string> modelVert, modelFrag;

	try {
		unsigned int i;
		csv::Parser file = csv::Parser(path);
		for (i=0; i < file.rowCount(); ++i) {
			modelPath.push_back(file[i][0]);
			modelPosition.push_back(vec3(stof(file[i][1]), stof(file[i][2]), stof(file[i][3])));
			modelRotation.push_back(vec3(stof(file[i][4]), stof(file[i][5]), stof(file[i][6])));
			modelVert.push_back(file[i][7]);
			modelFrag.push_back(file[i][8]);
		}

		for (i=0; i < modelPath.size(); ++i) {
			if (!load_model(modelPath.at(i), modelPosition.at(i),
				modelRotation.at(i), modelVert.at(i), modelFrag.at(i))) {
					return false;
			}
		}
	} catch (csv::Error &e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	return true;
} // load_prop_list(string path)

/*
* load_model
*
* Uses tinyobj to load the models from their .obj file
* then assigns the values extracted to the objects
*/
bool ContentManager::load_model(string modelPath, vec3 modelPosition, vec3 modelRotation,
	string modelVert, string modelFrag)
{
	std::vector<tinyobj::shape_t> shapes;
	std::string err = tinyobj::LoadObj(shapes, modelPath.c_str());

	if (!err.empty()) {
		std::cerr << err << std::endl;
		return false;
	}

	unsigned int i, j;
	for (i=0; i < shapes.size(); ++i) {
		assert((shapes[i].mesh.positions.size() % 3) == 0);
		shared_ptr<mesh> model = make_shared<mesh>();
		model->geom = make_shared<geometry>();

		for (j=0; j < shapes[i].mesh.positions.size() / 3 ; ++j) {
			model->geom->positions.push_back(vec3(shapes[i].mesh.positions[3*j+0],
				shapes[i].mesh.positions[3*j+1],
				shapes[i].mesh.positions[3*j+2]));

			model->geom->normals.push_back(vec3(shapes[i].mesh.normals[3*j+0],
				shapes[i].mesh.normals[3*j+1],
				shapes[i].mesh.normals[3*j+2]));
		}

		assert((shapes[i].mesh.texcoords.size() % 2) == 0);
		for (j=0; j < shapes[i].mesh.texcoords.size() / 2; ++j) {
			// Invert texture coordinates due to 3d max exporting issues
			model->geom->tex_coords.push_back(vec2(-shapes[i].mesh.texcoords[2*j+0],
				-shapes[i].mesh.texcoords[2*j+1]));
		}

		assert((shapes[i].mesh.indices.size() % 3) == 0);
		model->geom->indices = shapes[i].mesh.indices;

		geometry_builder::initialise_geometry(model->geom);

		auto eff = make_shared<effect>();
		eff->add_shader(modelVert, GL_VERTEX_SHADER);
		eff->add_shader(modelFrag, GL_FRAGMENT_SHADER);
		if (!effect_loader::build_effect(eff)) {
			return false;
		}

		model->mat = make_shared<material>();
		model->mat->effect = eff;

		// Set shader values for object
		model->mat->data.emissive = vec4(shapes[i].material.emission[0],
			shapes[i].material.emission[1],
			shapes[i].material.emission[2],
			shapes[i].material.transmittance[i]);

		model->mat->data.diffuse_reflection = vec4(shapes[i].material.diffuse[0],
			shapes[i].material.diffuse[1],
			shapes[i].material.diffuse[2],
			shapes[i].material.transmittance[i]);

		model->mat->data.specular_reflection = vec4(shapes[i].material.specular[0],
			shapes[i].material.specular[1],
			shapes[i].material.specular[2],
			shapes[i].material.transmittance[i]);

		model->mat->data.shininess = shapes[i].material.shininess;
		model->mat->set_uniform_value("eye_position", CameraManager::get_instance().currentCamera->get_position());

		model->mat->set_uniform_value("directional_light", SceneManager::get_instance().light);

		auto tex = texture_loader::load(shapes[i].material.diffuse_texname);
		model->mat->set_texture("tex", tex);

		if (!model->mat->build()) {
			return false;
		}

		model->trans.position = modelPosition;
		quat rot(modelRotation);
		model->trans.orientation = model->trans.orientation * rot;

		register_prop(*model);
	} // for shapes.size()

	return true;
} // load_model()