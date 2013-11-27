#include "contentmanager.h"

#pragma once

/* initialize : Initializes the ContentManager.  
 * 
 * Models described in the external proplist are loaded into the
 * ContentManagers proplist
 */
bool ContentManager::initialize()
{
    path = "proplist.csv";

    if (!load_skybox()) {
        cout << "Skybox failed to load" << '\n';
    }

    if (!load_props()) {
        cout << "Props failed to load" << '\n';
        return false;
    }

    _running = true;
    cout << "## ContentManager Initialised ##" << '\n';
    return true;
} // initialize()

/* load_skybox : loads the props for the scene
 *
 * Loads the stars for the solar system.
 */
bool ContentManager::load_skybox() {
    // Create skybox
    sky_box = make_shared<skybox>();

    // Load in cube map
    vector<string> filenames;
    filenames.push_back("stars_left2.png");
    filenames.push_back("stars_right1.png");
    filenames.push_back("stars_top3.png");
    filenames.push_back("stars_bottom4.png");
    filenames.push_back("stars_front5.png");
    filenames.push_back("stars_back6.png");
    sky_box->tex = texture_loader::load(filenames);

    // Load in skybox shader
    sky_box->eff = make_shared<effect>();
    sky_box->eff->add_shader("sky_box.vert", GL_VERTEX_SHADER);
    sky_box->eff->add_shader("sky_box.frag", GL_FRAGMENT_SHADER);
    if (!effect_loader::build_effect(sky_box->eff)){
        return false;
    }


} // load_skybox()

/* load_props : loads the props for the scene
 *
 * Loads Earth, Sputnik, Moon and Sun for the scene
 */
bool ContentManager::load_props()
{
    earth = Earth();
    sputnik = Sputnik();
    moon = Moon();

    // Load Earth
    if (!load_model(&earth, earth.get_path())) {
        return false;
    }
    // Load Sputnik
    if (!load_model(&sputnik, sputnik.get_path())) {
       return false;
    }

    // Load Moon
    if (!load_model(&moon, moon.get_path())) {
       return false;
    }

    // Add Earth meshes
    register_prop(&earth);
    // Add Sputnik meshes
    register_prop(&sputnik);
    // Add Moon meshes
    register_prop(&moon);

    return true;
} // load_props()

/* load_model : Loads the meshs for a Prop
 * 
 * Uses tinyobj to load the models from their .obj file
 * then assigns the values extracted to the objects
 */
bool ContentManager::load_model(Prop* prop, string modelPath)
{
    // Load .OBJ
    vector<tinyobj::shape_t> shapes;
    string err = tinyobj::LoadObj(shapes, modelPath.c_str());

    // If an error occured stop
    if (!err.empty()) {
        std::cerr << err << std::endl;
        return false;
    }

    unsigned int i;
    for (i=0; i < shapes.size(); ++i) {
        // Create mesh
        shared_ptr<mesh> model = make_shared<mesh>();
        model->geom = make_shared<geometry>();

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
        eff->add_shader(prop->get_frag_path(), GL_FRAGMENT_SHADER);
        // Build effect
        if (!effect_loader::build_effect(eff)) {
            return false;
        }

        // Create material and add effect
        model->mat = make_shared<material>();
        model->mat->effect = eff;
        
        load_shader_data(shape, model.get());

        // Set "eye position" and lighting for shader
        model->mat->set_uniform_value("eye_position", CameraManager::get_instance().currentCamera->get_position());
        model->mat->set_uniform_value("directional_light", SceneManager::get_instance().light);

        auto tex = texture_loader::load(shape->material.diffuse_texname);
        model->mat->set_texture("tex", tex);
        // build material
        if (!model->mat->build()) {
            return false;
        }

        model->trans.scale = prop->get_scale();
        quat rot(prop->get_rotation());
        model->trans.orientation = model->trans.orientation * rot;
        model->trans.position = prop->get_position();

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
void ContentManager::load_shader_data(tinyobj::shape_t * shape, mesh * model)
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
    for each (Prop* ptr_p in prop_list) {
        ptr_p->update();
    }
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
Prop* ContentManager::get_prop_at(int index)
{
    return prop_list.at(index);
} // get_prop_at()

/* register_prop : Adds prop to prop_list
 * 
 * Register object with scene manager for rendering
 */
void ContentManager::register_prop(Prop* prop)
{
    prop_list.push_back(prop);
} // register_prop()

/*  unregister_prop : Removes prop from prop_list
 *
 * Unregister object with scene manager
 */
void ContentManager::unregister_prop(Prop* prop)
{
    prop_list.push_back(prop);
} // unregister_prop()