#include "contentmanager.h"

// Model Classes
#include "Earth.h"
#include "Sputnik.h"

/* initialize : Initializes the ContentManager.  
 * 
 * Models described in the external proplist are loaded into the
 * ContentManagers proplist
 */
bool ContentManager::initialize()
{
    path = "proplist.csv";

    if (!load_prop_list(path)) {
        printf("Failed to read prop list, cannot render scene.\n");
        return false;
    }

    _running = true;
    return true;
} // initialize()

/* shutdown : Shuts down the ContentManager
 * 
 * Sets the ContentManager to stop running
 */
void ContentManager::shutdown()
{
    _running = false;
} // shutdown()

/* update : Updates all tracked objects
 * 
 * Updates objects in the proplist
 */
void ContentManager::update(float deltaTime)
{
    // TODO: Implement Props updating
} // update(float deltaTime)

/* prop_list_size : Returns the size of prop_list
* 
* returns the size of prop_list
*/
int ContentManager::prop_list_size()
{
    return prop_list.size();
} // prop_list_size()

/* get_prop_at : Returns prop at the given index
 * 
 * Parameter (int index) - index of prop
 *
 * Gets the prop at the index provided from
 * prop_list
 */
mesh ContentManager::get_prop_at(int index)
{
    mesh result = prop_list.at(index);
    return result;
} // get_prop_at()

/* register_prop : Adds prop to prop_list
 * 
 * Register object with scene manager for rendering
 */
void ContentManager::register_prop(mesh mesh)
{
    prop_list.push_back(mesh);
} // register_prop()

/*  unregister_prop : Removes prop from prop_list
 *
 * Unregister object with scene manager
 */
void ContentManager::unregister_prop(mesh mesh)
{
    prop_list.push_back(mesh);
} // unregister_prop()

/* load_prop_list : Loads props from propList.csv
 *
 * DEPRECATED:
 *
 * Parameter string path - Path for external proplist
 *
 * Loads models from external proplist in to the ContentManagers
 * interal proplist
 */
bool ContentManager::load_prop_list(string path)
{
    vector<string> modelPath;
    vector<vec3> modelPosition;
    vector<vec3> modelRotation;
    vector<string> modelVert, modelFrag;

    try {
        unsigned int i;
        csv::Parser file = csv::Parser(path);
        for (i = 0; i < file.rowCount(); ++i) {
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
} // load_prop_list()

/* load_props : loads the props for the scene
 *
 * Loads Earth, Sputnik, Moon and Sun for the scene
 */
bool ContentManager::load_props()
{
    Earth earth = Earth();
    Sputnik sputnik = Sputnik();

    // Load Earth
    if (!load_model(&sputnik, sputnik.get_path())) {
        return false;
    }

    // Load Sputnik
    if (!load_model(&sputnik, sputnik.get_path())) {
        return false;
    }

    return false;
} // load_props()

/* load_model : Loads the meshs for a Prop
 * 
 * Uses tinyobj to load the models from their .obj file
 * then assigns the values extracted to the objects
 */
bool ContentManager::load_model(Prop* prop, string modelPath)
{
    // Load .OBJ
    std::vector<tinyobj::shape_t> shapes;
    std::string err = tinyobj::LoadObj(shapes, modelPath.c_str());

    // If an error occured stop
    if (!err.empty()) {
        std::cerr << err << std::endl;
        return false;
    }

    // Create mesh
    shared_ptr<mesh> model = make_shared<mesh>();

    unsigned int i;
    for (i=0; i < shapes.size(); ++i) {
        tinyobj::shape_t* shape = &shapes[i];
        load_vertices(shape, model.get());
        load_normals(shape, model.get());
        load_texcoords(shape, model.get());
        load_indices(shape, model.get());
        
        // Initialise all loaded geometry data
        geometry_builder::initialise_geometry(model->geom);

        // Created effect for mesh
        auto eff = make_shared<effect>();
        eff->add_shader(prop->get_vert_path(), GL_VERTEX_SHADER);
        eff->add_shader(prop->get_vert_path(), GL_FRAGMENT_SHADER);
        // Build effect
        if (!effect_loader::build_effect(eff)) {
            return false;
        }

        // Create material and add effect
        model->mat = make_shared<material>();
        model->mat->effect = eff;
        
        // Set "eye position" and lighting for shader
        model->mat->set_uniform_value("eye_position", CameraManager::get_instance().currentCamera->get_position());
        model->mat->set_uniform_value("directional_light", SceneManager::get_instance().light);

        auto tex = texture_loader::load(shape->material.diffuse_texname);
        model->mat->set_texture("tex", tex);
        // build material
        if (!model->mat->build()) {
            return false;
        }

        model->trans.position = prop->get_position();
        quat rot(prop->get_rotation());
        model->trans.orientation = model->trans.orientation * rot;

        prop->add_mesh(model.get());
    } // for each in shapes[]

    return true;
} // load_model()

/** load_vertices : Loads vertices from shape
 *
 * Loads all shape positions and produces the vertices for the mesh
 */
void ContentManager::load_vertices(tinyobj::shape_t * shape, mesh * model)
{
    // Check ptrs are not null.
    if (shape != nullptr && model != nullptr) {
        // Check there are enough points to make full vertexes
        assert((shape->mesh.positions.size() % 3) == 0);
        unsigned int i;
        for (i=0; i < shape->mesh.positions.size() / 3 ; ++i) {
            model->geom->positions.push_back(vec3(shape->mesh.positions[3*i+0],
                                                  shape->mesh.positions[3*i+1],
                                                  shape->mesh.positions[3*i+2]));
        }
    }
} // load_vertices()

/** load_normals : Loads vertices from shape
 *
 * Loads all shape normals and add them to the mesh
 */
void ContentManager::load_normals(tinyobj::shape_t * shape, mesh * model)
{
    // Check ptrs are not null.
    if (shape != nullptr && model != nullptr) {
        // Check there are enough points for normals
        assert((shape->mesh.positions.size() % 3) == 0);
        unsigned int i;
        for (i=0; i < shape->mesh.positions.size() / 3 ; ++i) {
            model->geom->normals.push_back(vec3(shape->mesh.normals[3*i+0],
                                                shape->mesh.normals[3*i+1],
                                                shape->mesh.normals[3*i+2]));
        }
    }
} // load_normals()

/** load_texcoords : Loads vertices from shape
 *
 * Loads all shape tex coords and add them to the mesh
 */
void ContentManager::load_texcoords(tinyobj::shape_t * shape, mesh * model)
{
    // Check ptrs are not null.
    if (shape != nullptr && model != nullptr) {
        // Check there are enough points to make tex coords
        assert((shape->mesh.texcoords.size() % 2) == 0);
        unsigned int i;
        for (i = 0; i < shape->mesh.texcoords.size() / 2; ++i) {
            // Invert texture coordinates due to 3d max exporting issues
            model->geom->tex_coords.push_back(vec2(-shape->mesh.texcoords[2*i+0],
                                                   -shape->mesh.texcoords[2*i+1]));
        }
    }
} // load_texcoords()

/** load_indices : Loads vertices from shape
 *
 * Loads all shape indices and add them to the mesh
 */
void ContentManager::load_indices(tinyobj::shape_t * shape, mesh * model)
{
    // Check ptrs are not null.
    if (shape != nullptr && model != nullptr) {
        assert((shape->mesh.indices.size() % 3) == 0);
        model->geom->indices = shape->mesh.indices;
    }
} // load_indices()

/* load_shader_data : Loads shader data
 *
 * Loads shader data from shape and applies it to the effect for model
 */
void load_shader_data(tinyobj::shape_t * shape, mesh * model)
{
    // Set shader values for object
    model->mat->data.emissive            = vec4(shape->material.emission[0],
                                                shape->material.emission[1],
                                                shape->material.emission[2],
                                                // current used .mtl files only store 
                                                // one value for Tr (transmittance)
                                                shape->material.transmittance[0]);

    model->mat->data.diffuse_reflection  = vec4(shape->material.diffuse[0],
                                                shape->material.diffuse[1],
                                                shape->material.diffuse[2],
                                                // current used .mtl files only store 
                                                // one value for Tr (transmittance)
                                                shape->material.transmittance[0]);

    model->mat->data.specular_reflection = vec4(shape->material.specular[0],
                                                shape->material.specular[1],
                                                shape->material.specular[2],
                                                // current used .mtl files only store 
                                                // one value for Tr (transmittance)
                                                shape->material.transmittance[0]);

    model->mat->data.shininess = shape->material.shininess;
} // load_shader_data()

/* load_model : Loads models
* 
* DEPRECATED:
*
* Uses tinyobj to load the models from their .obj file
* then assigns the values extracted to the objects
*/
bool ContentManager::load_model(string modelPath, vec3 modelPosition, vec3 modelRotation,
    string modelVert, string modelFrag)
{
    // Create and load .OBJ
    std::vector<tinyobj::shape_t> shapes;
    std::string err = tinyobj::LoadObj(shapes, modelPath.c_str());

    // If an error occured stop
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