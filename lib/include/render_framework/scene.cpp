#include "scene.h"
#include "geometry.h"
#include "content_manager.h"

namespace render_framework
{
	// Helper method to extract a 2D vector from property tree
	glm::vec2 scene_loader::read_vec2(const boost::property_tree::ptree& pt)
	{
		glm::vec2 v;
		// Get the value from the property tree
		auto iter = pt.begin();
		// Extract vector values
		v.x = (iter++)->second.get_value<float>();
		v.y = (iter++)->second.get_value<float>();
		// Return extracted vector
		return v;
	}

	// Helper method to extract a 3D vector from property tree
	glm::vec3 scene_loader::read_vec3(const boost::property_tree::ptree& pt)
	{
		glm::vec3 v;
		// Get the value from the property tree
		auto iter = pt.begin();
		// Extract vector values
		v.x = (iter++)->second.get_value<float>();
		v.y = (iter++)->second.get_value<float>();
		v.z = (iter++)->second.get_value<float>();
		// Return extracted vector
		return v;
	}

	// Helper method to extract a 4D vector from property tree
	glm::vec4 scene_loader::read_vec4(const boost::property_tree::ptree& pt)
	{
		glm::vec4 v;
		// Get the value from the property tree
		auto iter = pt.begin();
		// Extract vector values
		v.x = (iter++)->second.get_value<float>();
		v.y = (iter++)->second.get_value<float>();
		v.z = (iter++)->second.get_value<float>();
		v.w = (iter++)->second.get_value<float>();
		// Return extracted vector
		return v;
	}

	void scene_loader::read_geometry(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// Loop through the values in the geometry subtree
		for (auto& val : pt)
		{
			// Get the name from the geometry node
			auto name = val.first;
			try
			{
				// Extract the type
				auto type = val.second.get_child("type").get_value<std::string>();
				// Check the type and act accordingly
				if (type == "box")
				{
					// Extract dimensions
					auto dim = read_vec3(val.second.get_child("dimensions"));
					// Create box
					auto box = geometry_builder::create_box(dim);
					// Add to the scene data and content manager
					data->geometry[name] = box;
					content_manager::get_instance().add(name, box);
					// Log
					std::clog << "Added box geometry " << name << std::endl;
				}
				else if (type == "tetrahedron")
				{
					// Extract dimensions
					auto dim = read_vec3(val.second.get_child("dimensions"));
					// Create tetrahedron
					auto tetra = geometry_builder::create_tetrahedron(dim);
					// Add to the scene data and content manager
					data->geometry[name] = tetra;
					content_manager::get_instance().add(name, tetra);
					// Log
					std::clog << "Added tetrahedron geometry " << name << std::endl;
				}
				else if (type == "pyramid")
				{
					// Extract dimensions
					auto dim = read_vec3(val.second.get_child("dimensions"));
					// Create pyramid
					auto pyr = geometry_builder::create_pyramid(dim);
					// Add to the scene data and content manager
					data->geometry[name] = pyr;
					content_manager::get_instance().add(name, pyr);
					// Log
					std::clog << "Added pyramid geometry " << name << std::endl;
				}
				else if (type == "disk")
				{
					// Extract dimensions
					auto dim = read_vec2(val.second.get_child("dimensions"));
					// Extract slices
					auto slices = val.second.get_child("slices").get_value<int>();
					// Create disk
					auto disk = geometry_builder::create_disk(slices, dim);
					// Add to the scene data and content manager
					data->geometry[name] = disk;
					content_manager::get_instance().add(name, disk);
					// Log
					std::clog << "Added disk geometry " << name << std::endl;
				}
				else if (type == "cylinder")
				{
					// Extract dimensions
					auto dim = read_vec3(val.second.get_child("dimensions"));
					// Extract slices and stacks
					auto slices = val.second.get_child("slices").get_value<int>();
					auto stacks = val.second.get_child("stacks").get_value<int>();
					// Create cylinder
					auto cyl = geometry_builder::create_cylinder(stacks, slices, dim);
					// Add to the scene data and content manager
					data->geometry[name] = cyl;
					content_manager::get_instance().add(name, cyl);
					// Log
					std::clog << "Added cylinder geometry " << name << std::endl;
				}
				else if (type == "sphere")
				{
					// Extract dimensions
					auto dim = read_vec3(val.second.get_child("dimensions"));
					// Extract slices and stacks
					auto slices = val.second.get_child("slices").get_value<int>();
					auto stacks = val.second.get_child("stacks").get_value<int>();
					// Create sphere
					auto sphere = geometry_builder::create_sphere(stacks, slices, dim);
					// Add to the scene data and content manager
					data->geometry[name] = sphere;
					content_manager::get_instance().add(name, sphere);
					// Log
					std::clog << "Added sphere geometry " << name << std::endl;
				}
				else if (type == "sphere-subdivision")
				{
					// Extract dimensions
					auto dim = read_vec3(val.second.get_child("dimensions"));
					// Extract subdivisions
					auto div = val.second.get_child("divisions").get_value<int>();
					// Create sphere
					auto sphere = geometry_builder::create_sphere_subdivision(div, dim);
					// Add to the scene data and content manager
					data->geometry[name] = sphere;
					content_manager::get_instance().add(name, sphere);
					// Log
					std::clog << "Added sphere geometry " << name << std::endl;
				}
				else if (type == "torus")
				{
					// Extract stacks and slices
					auto slices = val.second.get_child("slices").get_value<int>();
					auto stacks = val.second.get_child("stacks").get_value<int>();
					// Extract radii
					auto ring_radius = val.second.get_child("ring-radius").get_value<float>();
					auto outer_radius = val.second.get_child("outer-radius").get_value<float>();
					// Create torus
					auto torus = geometry_builder::create_torus(stacks, slices, ring_radius, outer_radius);
					// Add to the scene data and content manager
					data->geometry[name] = torus;
					content_manager::get_instance().add(name, torus);
					// Log
					std::clog << "Added torus geometry " << name << std::endl;
				}
				else if (type == "plane")
				{
					// Extract width and depth
					auto width = val.second.get_child("width").get_value<int>();
					auto depth = val.second.get_child("depth").get_value<int>();
					// Create plane
					auto plane = geometry_builder::create_plane(width, depth);
					// Add to the scene data and content manager
					data->geometry[name] = plane;
					content_manager::get_instance().add(name, plane);
					// Log
					std::clog << "Added plane geometry " << name << std::endl;
				}
				else if (type == "sierpinski")
				{
					// Extract divisions
					auto div = val.second.get_child("divisions").get_value<int>();
					// Create gasket
					auto gasket = geometry_builder::create_sierpinski(div);
					// Add to the scene data
					data->geometry[name] = gasket;
					content_manager::get_instance().add(name, gasket);
					// Log
					std::clog << "Added sierpinski geometry " << name << std::endl;
				}
				else
				{
					// Geometry type not recognised
					std::cerr << "ERROR - geometry type not recognised: " << type << std::endl;
				}
			}
			catch (std::exception)
			{
				// Something happened during extraction
				std::cerr << "ERROR - extracting geometry information from scene file" << std::endl;
				std::cerr << name << " ill formed" << std::endl;
			}
		}
	}

	void scene_loader::read_materials(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// Loop through values in material sub-tree
		for (auto& m : pt)
		{
			// Extract name
			auto name = m.first;
			// Try and extract values
			try
			{
				// Create material object
				auto mat = std::make_shared<material>();
				// Now extract each individual material value
				for (auto& val : m.second)
				{
					// Extract name of value
					auto value_name = val.first;
					// Extract type
					auto type = val.second.get_child("type").get_value<std::string>();
					// Extract value based on type
					if (type == "int")
					{
						// Extract value
						auto value = val.second.get_child("value").get_value<int>();
						// Set uniform value
						mat->set_uniform_value(name, value);
					}
					else if (type == "double")
					{
						// Extract value
						auto value = val.second.get_child("value").get_value<double>();
						// Set uniform value
						mat->set_uniform_value(name, value);
					}
					else if (type == "float")
					{
						// Extract value
						auto value = val.second.get_child("value").get_value<float>();
						// Set uniform value
						mat->set_uniform_value(name, value);
					}
					else if (type == "unsigned int")
					{
						// Extract value
						auto value = val.second.get_child("value").get_value<unsigned int>();
						// Set uniform value
						mat->set_uniform_value(name, value);
					}
					else if (type == "vec2")
					{
						// Extract value
						auto value = read_vec2(val.second.get_child("value"));
						// Set uniform value
						mat->set_uniform_value(name, value);
					}
					else if (type == "vec3")
					{
						// Extract value
						auto value = read_vec3(val.second.get_child("value"));
						// Set uniform value
						mat->set_uniform_value(name, value);
					}
					else if (type == "mat2")
					{
						// ???
						// TODO
						std::clog << "mat2 JSON reading not implemented" << std::endl;
					}
					else if (type == "mat3")
					{
						// ???
						// TODO
						std::clog << "mat3 JSON reading not implemented" << std::endl;
					}
					else if (type == "mat4")
					{
						// ???
						// TODO
						std::clog << "mat4 JSON reading not implemented" << std::endl;
					}
					else if (type == "texture")
					{
						// Extract texture name
						auto tex_name = val.second.get_child("value").get_value<std::string>();
						// Get texture from scene data
						auto tex = data->textures[tex_name];
						// Set uniform value
						mat->set_texture(name, tex);
					}
					else
					{
						// Data type not recognised
						std::cerr << "ERROR - material value type " << type << " not recognised" << std::endl;
					}
				}
				// Add material to scene data and content manager then log
				data->materials[name] = mat;
				content_manager::get_instance().add(name, mat);
				std::clog << "Added material " << name << std::endl;
			}
			catch (std::exception e)
			{
				// Something happened during extraction
				std::cerr << "ERROR - extracting material information from scene file" << std::endl;
				std::cerr << name << " ill formed" << std::endl;
			}
		}
	}

	void scene_loader::read_transform(std::shared_ptr<mesh> mesh, const boost::property_tree::ptree& pt)
	{
		// Try and extract values from scene file
		try
		{
			// Extract position value
			mesh->trans.position = read_vec3(pt.get_child("position"));
			// Extract rotation value
			mesh->trans.orientation = glm::quat(read_vec3(pt.get_child("rotation")));
			// Extract scale value
			mesh->trans.scale = read_vec3(pt.get_child("scale"));
		}
		catch (std::exception e)
		{
			// Error extracting values
			std::cerr << "ERROR - extracting transform values" << std::endl;
		}
	}

	void scene_loader::read_meshes(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// Loop through each entry in the mesh sub-tree
		for (auto& m : pt)
		{
			// Extract name
			auto name = m.first;
			// try and extract other values
			try
			{
				// Create mesh object
				auto mesh_object = std::make_shared<mesh>();
				// Extract geometry to use
				auto geom = m.second.get_child("geometry").get_value<std::string>();
				// Get geometry from scene data
				mesh_object->geom = data->geometry[geom];
				// Extract material to use
				auto mat = m.second.get_child("material").get_value<std::string>();
				// Get geometry from scene data
				mesh_object->mat = data->materials[mat];
				// Read in transform
				read_transform(mesh_object, pt.get_child("transform"));
				// Add mesh to scene data and content manager then log
				data->meshes[name] = mesh_object;
				content_manager::get_instance().add(name, mesh_object);
				std::clog << "Added mesh " << name << std::endl;
			}
			catch (std::exception e)
			{
				// Error trying to read in mesh information
				std::cout << "ERROR - could not read in data for mesh " << name << std::endl;
			}
		}
	}

	void scene_loader::read_lighting(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// Initialise scene lighting
		data->scene_light = std::make_shared<directional_light>();
		// try and read lighting values
		try
		{
			// Extract ambient value
			data->scene_light->data.ambient_intensity = read_vec4(pt.get_child("ambient-intensity"));
			// Extract light colour
			data->scene_light->data.colour = read_vec4(pt.get_child("colour"));
			// Extract light direction
			data->scene_light->data.direction = read_vec3(pt.get_child("direction"));
			// Try and build light
			if (!content_manager::get_instance().build(data->name + "_scene_light", data->scene_light))
			{
				// Light failed to build - display error
				std::cerr << "ERROR - could not build scene lighting" << std::endl;
				// Set the scene light to nullptr
				data->scene_light = nullptr;
			}
			else
				// Log
				std::clog << "Scene lighting loaded" << std::endl;
		}
		catch (std::exception e)
		{
			std::cerr << "ERROR - could not read scene lighting values" << std::endl;
		}
	}

	void scene_loader::read_point_light(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// Create a point light
		point_light_data point;
		// try and read point light values
		try
		{
			// Read in colour
			point.colour = read_vec4(pt.get_child("colour"));
			// Read in attenuation
			point.attenuation = read_vec3(pt.get_child("attenuation"));
			// Read in position
			point.position = read_vec3(pt.get_child("position"));
			// Add the point light to the scene data
			data->lights->data.point_lights.push_back(point);
		}
		catch (std::exception e)
		{
			std::cerr << "ERROR - could not read point light value" << std::endl;
		}
	}

	void scene_loader::read_spot_light(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// Create a spot light
		spot_light_data spot;
		// try and read spot light values
		try
		{
			// Read in colour
			spot.colour = read_vec4(pt.get_child("colour"));
			// Read in attenuation
			spot.attenuation = read_vec3(pt.get_child("attenuation"));
			// Read in position
			spot.position = read_vec3(pt.get_child("position"));
			// Read in direction
			spot.direction = read_vec3(pt.get_child("direction"));
			// Read in power
			spot.power = pt.get_child("power").get_value<float>();
			// Add the spot light to the scene data
			data->lights->data.spot_lights.push_back(spot);
		}
		catch (std::exception e)
		{
			std::cerr << "ERROR - could not read spot light value" << std::endl;
		}
	}

	void scene_loader::read_dynamic_lights(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// Initialise dynamic lighting
		data->lights = std::make_shared<dynamic_lights>();
		// Loop through the dynamic lights and act accordingly
		for (auto& l : pt)
		{
			// Extract first
			auto type = l.first;
			// Check type and read accordingly
			if (type == "point")
				read_point_light(data, l.second);
			else if (type == "spot")
				read_spot_light(data, l.second);
			else
			{
				// Unrecognised type
				std::cerr << "ERROR - unknown light type encountered: " << type << std::endl;
			}
		}
		// Try and build dynamic lights
		if (!content_manager::get_instance().build(data->name + "_dynamic_light", data->lights))
		{
			std::cerr << "ERROR - could not build dynamic lights for scene" << std::endl;
			data->lights = nullptr;
		}
		else
			// Log
			std::clog << "Scene dynamic lights loaded" << std::endl;
	}

	void scene_loader::read_textures(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// Loop through each texture
		for (auto& tex : pt)
		{
			// Extract the name
			auto name = tex.first;
			// Extract the filename
			auto filename = tex.second.get_value<std::string>();
			// Try and load the texture
			auto tex_object = content_manager::get_instance().load<texture>(filename);
			// If texture is loaded (not nullptr) add to data
			if (tex_object != nullptr)
			{
				// Add to textures and log
				data->textures[name] = tex_object;
				std::clog << "Texture " << name << " loaded" << std::endl;
			}
			else
				// Display error
				std::cerr << "ERROR - could not load texture " << name << " using filename " << filename << std::endl;
		}
	}

	void scene_loader::read_prodedural_textures(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// TODO
	}

	void scene_loader::read_models(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// TODO
	}

	void scene_loader::read_terrain(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// TODO
	}

	void scene_loader::read_shaders(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// Loop through each shader
		for (auto& s : pt)
		{
			// Get the name
			auto name = s.first;
			// try and get the filename and type
			try
			{
				// Get the filename
				auto filename = s.second.get_child("filename").get_value<std::string>();
				// Get the type
				auto type = s.second.get_child("type").get_value<std::string>();
				// Get the type of the shader
				GLenum shader_type;
				if (type == "VERTEX")
					shader_type = GL_VERTEX_SHADER;
				else if (type == "FRAGMENT")
					shader_type = GL_FRAGMENT_SHADER;
				else if (type == "GEOMETRY")
					shader_type = GL_GEOMETRY_SHADER;
				else
				{
					// Type not recognied.  Display error and continue
					std::cerr << "ERROR - did not recognise shader type " << type << " for shader " << name << std::endl;
					continue;
				}
				// Try and load the shader based on type
				auto shader = content_manager::get_instance().load(filename, shader_type);
				// Check if loaded
				if (shader != nullptr)
				{
					// Add to scene data and log
					data->shaders[name] = shader;
					std::clog << "Shader " << name << " loaded" << std::endl;
				}
				else
					// Display error
					std::cerr << "ERROR - could not load shader " << name << std::endl;
			}
			catch (std::exception e)
			{
				std::cerr << "ERROR - reading in shader " << name << std::endl;
			}
		}
	}

	void scene_loader::read_effects(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// Loop through each effect
		for (auto& e : pt)
		{
			// Extract the name of the effect
			auto name = e.first;
			// Create a new effect
			auto eff = std::make_shared<effect>();
			// Now loop through each value associated with the name
			for (auto& s : e.second)
			{
				// Get the name of the shader
				auto shader_name = s.second.get_value<std::string>();
				// Try and extract from scene data
				auto found = data->shaders.find("shader_name");
				if (found == data->shaders.end())
				{
					// Shader not in scene data - display error
					std::cerr << "ERROR - creating effect " << name << ". Shader " << shader_name << " not found." << std::endl;
					// We will still continue - might be able to save this
				}
				else
				{
					// Add shader to the effect
					eff->add_shader(found->second);
				}
			}
			// We've attached all necessary shaders - attempt to build
			if (!content_manager::get_instance().build(name, eff))
			{
				// Couldn't build effect - display error
				std::cerr << "ERROR - could not build effect " << name << std::endl;
			}
			else
			{
				// Successfully built - add to scene data and log
				data->effects[name] = eff;
				std::clog << "Effect " << name << " successfully built" << std::endl;
			}
		}
	}

	void scene_loader::read_render_passes(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// TODO
	}

	void scene_loader::read_post_processes(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// TODO
	}

	void scene_loader::read_cube_maps(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt)
	{
		// TODO
	}

	std::shared_ptr<scene_data> scene_loader::load_scene(const std::string& filename)
	{
		// try and read in the scene data
		try
		{
			// Create scene object
			std::shared_ptr<scene_data> data = std::make_shared<scene_data>();
			// Create property treee object
			boost::property_tree::ptree pt;
			// Read in JSON file to populate property tree
			boost::property_tree::read_json(filename, pt);

			// Now read in the scene data
			// Geometry
			read_geometry(data, pt.get_child("geometry"));
			// Models
			read_models(data, pt.get_child("models"));
			// Terrain
			read_terrain(data, pt.get_child("terrain"));
			// Textures
			read_textures(data, pt.get_child("textures"));
			// Procedural textures
			read_prodedural_textures(data, pt.get_child("procedural_textures"));
			// Cube maps
			read_cube_maps(data, pt.get_child("cube_maps"));
			// Lighting
			read_lighting(data, pt.get_child("lighting"));
			read_dynamic_lights(data, pt.get_child("dynamic_lights"));
			// Shaders
			read_shaders(data, pt.get_child("shaders"));
			// Effects
			read_effects(data, pt.get_child("effects"));
			// Materials
			read_materials(data, pt.get_child("materials"));
			// Meshes
			read_meshes(data, pt.get_child("meshes"));
			// Render passes and post processes
			read_render_passes(data, pt.get_child("render_passes"));
			read_post_processes(data, pt.get_child("post_processes"));
			
			// Everything read - return read data
			return data;
		}
		catch (std::exception e)
		{
			// Error while reading.  Display error and return nullptr
			std::cerr << "ERROR - could not read scene data from " << filename << std::endl;
			return nullptr;
		}
	}

	bool scene_manager::add_scene(const std::string& filename)
	{
		return false;
	}

	bool scene_manager::add_scene(const std::string& name, std::shared_ptr<scene_data> scene)
	{
		return false;
	}

	bool scene_manager::remove_scene(const std::string& name)
	{
		return false;
	}

	bool scene_manager::load_scene(const std::string& name)
	{
		return false;
	}

	bool scene_manager::unload_scene(const std::string& name)
	{
		return false;
	}

	std::shared_ptr<scene_data> scene_manager::get_scene(const std::string& name) const
	{
		return nullptr;
	}

	std::shared_ptr<scene_data> scene_manager::get_current() const
	{
		return _current;
	}
}