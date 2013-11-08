#include "contentmanager.h"

#include <iostream>
#include <GLM\glm.hpp>

#include "tiny_obj_loader.h"
#include "CSVparser.hpp"
#include "cameramanager.h"
#include "scenemanager.h"

using namespace std;
using namespace glm;

bool ContentManager::initialize() {
    cout << "## Initializing ContentManager ##" << endl;

    path = "proplist.csv";

    if (!loadPropList(path)) {
        printf("Failed to read prop list, cannot render scene.\n");
        return false;
    }

    // Testing
    //mesh box = mesh();
    //box.geom = geometry_builder::create_box();
    //box.trans.translate(vec3(0.0, 0.0, 0.0));

    //registerProp(box);

    _running = true;

    cout << "## Initialized ContentManager ##" << endl;
    return true;
}

void ContentManager::update(float deltaTime) {}


bool ContentManager::loadPropList(string path) {
    cout << "## Loading prop list ##" << endl;
    printf("Loading Scene from %s.\n", path.c_str());

    vector<string> modelPath;
    vector<vec3> modelPosition;
    vector<vec3> modelRotation;
    vector<string> modelVert, modelFrag;

    try {
        cout << "Parsing file" << endl;
        csv::Parser file = csv::Parser(path);
        cout << "Finished parsing file" << endl;
        int i;
        cout << "Loading prop list" << endl;
        for (i=0; i < file.rowCount(); ++i) {
            modelPath.push_back(file[i][0]);
            modelPosition.push_back(vec3(stof(file[i][1]), stof(file[i][2]), stof(file[i][3])));
            modelRotation.push_back(vec3(stof(file[i][4]), stof(file[i][5]), stof(file[i][6])));
            modelVert.push_back(file[i][7]);
            modelFrag.push_back(file[i][8]);
        }
        cout << "Finished loading prop list" << endl;

        cout << "Loading prop" << endl;
        for (i=0; i < modelPath.size(); ++i) {
            if (!loadModel(modelPath.at(i), modelPosition.at(i), modelRotation.at(i), modelVert.at(i), modelFrag.at(i))) {
                return false;
            }
        }
        cout << "Finished loading prop" << endl;

    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }


    cout << "## Loaded prop list ##" << endl;
    return true;
}


bool ContentManager::loadModel(string modelPath, vec3 modelPosition, vec3 modelRotation, string modelVert, string modelFrag) {
    cout << "## Loading Model ##" << endl;

    std::vector<tinyobj::shape_t> shapes;

    cout << "## tinyobjloader loading file ##" << endl;
    std::string err = tinyobj::LoadObj(shapes, modelPath.c_str());
    cout << "## tinyobjloader loaded file ##" << endl;

    if (!err.empty()) {
        std::cerr << err << std::endl;
        return false;
    }


    cout << "## Loading model data ##" << endl;
    int i, j;
    for (i=0; i < shapes.size(); ++i) {
        assert((shapes[i].mesh.positions.size() % 3) == 0);
        cout << "Loading model " << shapes[i].name << endl;
        shared_ptr<mesh> model = make_shared<mesh>();
        model->geom = make_shared<geometry>();

        cout << "Loading " << shapes[i].mesh.positions.size() << " positions and " << shapes[i].mesh.normals.size() << " normals" << endl;
        for (j=0; j < shapes[i].mesh.positions.size() / 3 ; ++j) {
            model->geom->positions.push_back(vec3(shapes[i].mesh.positions[3*j+0],
                                                  shapes[i].mesh.positions[3*j+1],
                                                  shapes[i].mesh.positions[3*j+2]));

            model->geom->normals.push_back(vec3(shapes[i].mesh.normals[3*j+0],
                                                shapes[i].mesh.normals[3*j+1],
                                                shapes[i].mesh.normals[3*j+2]));
        }

        assert((shapes[i].mesh.texcoords.size() % 2) == 0);
        cout << "Loading " << shapes[i].mesh.texcoords.size() << " texcoords" << endl;
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

        // Set shader data here!

        // Set shader values for object
        model->mat->data.emissive = vec4(shapes[i].material.emission[0], shapes[i].material.emission[1], shapes[i].material.emission[2], shapes[i].material.transmittance[i]);
        model->mat->data.diffuse_reflection = vec4(shapes[i].material.diffuse[0], shapes[i].material.diffuse[1], shapes[i].material.diffuse[2], shapes[i].material.transmittance[i]);
        model->mat->data.specular_reflection = vec4(shapes[i].material.specular[0], shapes[i].material.specular[1], shapes[i].material.specular[2], shapes[i].material.transmittance[i]);
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

        registerProp(*model);
    }

    cout << "## Model Loaded ##" << endl;

    return true;
}


/*
* Register object with scene manager for rendering
*/
void ContentManager::registerProp(mesh object)
{
    printf("propList has %d members.\n", propList.size());
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