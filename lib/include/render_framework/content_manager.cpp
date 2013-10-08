#include "content_manager.h"
#include "geometry.h"
#include "model.h"
#include "terrain.h"
#include "texture.h"
#include "skybox.h"
#include "material.h"
#include "mesh.h"
#include "light.h"
#include "effect.h"
#include "frame_buffer.h"
#include "post_process.h"

namespace render_framework
{
	/*
	Unloads all the content currently associated with the content manager
	*/
	void content_manager::unload_content()
	{
		// Our job here is to iterate through each collection of content and
		// delete each value.
		// Start with geometry
		std::clog << "Deleting geometry" << std::endl;
		_geometry.clear();
		std::clog << "Geometry deleted" << std::endl;

		// Now delete models
		std::clog << "Deleting models" << std::endl;
		_models.clear();
		std::clog << "Models deleted" << std::endl;

		// Delete textures
		std::clog << "Deleting textures" << std::endl;
		_textures.clear();
		std::clog << "Textures deleted" << std::endl;

		// Delete cube maps
		std::clog << "Deleting cube maps" << std::endl;
		_cube_maps.clear();
		std::clog << "Cube maps deleted" << std::endl;

		// Delete sky boxes
		std::clog << "Deleting sky boxes" << std::endl;
		_skyboxes.clear();
		std::clog << "Sky boxes deleted" << std::endl;

		// Delete terrain
		std::clog << "Deleting terrain" << std::endl;
		_terrain.clear();
		std::clog << "Terrain deleted" << std::endl;

		// Delete materials
		std::clog << "Deleting materials" << std::endl;
		_materials.clear();
		std::clog << "Materials deleted" << std::endl;

		// Delete meshes
		std::clog << "Deleting meshes" << std::endl;
		_meshes.clear();
		std::clog << "Meshes deleted" << std::endl;

		// Delete directional lights
		std::clog << "Deleting directional lights" << std::endl;
		_directional_lights.clear();
		std::clog << "Directional lights deleted" << std::endl;

		// Delete point lights
		std::clog << "Deleting point lights" << std::endl;
		_point_lights.clear();
		std::clog << "Point lights deleted" << std::endl;

		// Delete spot lights
		std::clog << "Deleting spot lights" << std::endl;
		_spot_lights.clear();
		std::clog << "Spot lights deleted" << std::endl;

		// Delete dynamic lights
		std::clog << "Deleting dynamic lighting" << std::endl;
		_dynamic_lights.clear();
		std::clog << "Dynamic lights deleted" << std::endl;

		// Delete shaders
		std::clog << "Deleting shaders" << std::endl;
		_shaders.clear();
		std::clog << "Shaders deleted" << std::endl;

		// Delete effects
		std::clog << "Deleting effects" << std::endl;
		_effects.clear();
		std::clog << "Effects deleted" << std::endl;

		// Delete frame buffers
		std::clog << "Deleting frame buffers" << std::endl;
		_frame_buffers.clear();
		std::clog << "Frame buffers deleted" << std::endl;

		// Delete depth buffers
		std::clog << "Deleting depth buffers" << std::endl;
		_depth_buffers.clear();
		std::clog << "Depth buffers deleted" << std::endl;

		// Delete shadow maps
		std::clog << "Deleting shadow maps" << std::endl;
		_shadow_maps.clear();
		std::clog << "Shadow maps deleted" << std::endl;

		// Delete render passes
		std::clog << "Deleting render passes" << std::endl;
		_render_passes.clear();
		std::clog << "Render passes deleted" << std::endl;

		// Delete post processes
		std::clog << "Deleting post processes" << std::endl;
		_post_processes.clear();
		std::clog << "Post processes deleted" << std::endl;

		// All content has been deleted.  Print log message
		std::clog << "All content deleted" << std::endl;
	}

	/*
	Gets a piece of geometry from the content manager.  If geometry doesn't 
	exist, will return nullptr
	*/
	template <>
	std::shared_ptr<geometry> content_manager::get(const std::string& name)
	{
		// Try and find geometry
		auto found = _geometry.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _geometry.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a model from the content manager.  If model doesn't exist, will return
	nullptr
	*/
	template <>
	std::shared_ptr<model> content_manager::get(const std::string& name)
	{
		// Try and find model
		auto found = _models.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _models.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a texture from the content manager.  If texture doesn't exist, will 
	return nullptr
	*/
	template <>
	std::shared_ptr<texture> content_manager::get(const std::string& name)
	{
		// Try and find texture
		auto found = _textures.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _textures.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a cube map from the content manager.  If cube map doesn't exist, will
	return nullptr
	*/
	template <>
	std::shared_ptr<cube_map> content_manager::get(const std::string& name)
	{
		// Try and get cube map
		auto found = _cube_maps.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _cube_maps.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a skybox from the content manager.  If sky box doesn't exist, will
	return nullptr
	*/
	template <>
	std::shared_ptr<skybox> content_manager::get(const std::string& name)
	{
		// Try and get skybox
		auto found = _skyboxes.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _skyboxes.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a piece of terrain from the content manager.  If terrain doesn't exist,
	will return nullptr
	*/
	template <>
	std::shared_ptr<terrain> content_manager::get(const std::string& name)
	{
		// Try and get terrain
		auto found = _terrain.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _terrain.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a material from the content manager.  If material doesn't exist, will
	return nullptr
	*/
	template <>
	std::shared_ptr<material> content_manager::get(const std::string& name)
	{
		// Try and get material
		auto found = _materials.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _materials.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a mesh from the content manager.  If mesh doesn't
	exist, will return nullptr
	*/
	template <>
	std::shared_ptr<mesh> content_manager::get(const std::string& name)
	{
		// Try and get render object
		auto found = _meshes.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _meshes.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a directional light from the content manager.  If directional light
	doesn't exist, will return nullptr
	*/
	template <>
	std::shared_ptr<directional_light> content_manager::get(const std::string& name)
	{
		// Try and get directional light
		auto found = _directional_lights.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _directional_lights.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a point light from the content manager.  If point light doesn't exist,
	will return nullptr
	*/
	template <>
	std::shared_ptr<point_light> content_manager::get(const std::string& name)
	{
		// Try and get directional light
		auto found = _point_lights.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _point_lights.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a spot light from the content manager.  If spot light doesn't exist, 
	will return nullptr
	*/
	template <>
	std::shared_ptr<spot_light> content_manager::get(const std::string& name)
	{
		// Try and get spot light
		auto found = _spot_lights.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _spot_lights.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a set of dynamic lights from the content manager.  If light doesn't
	exist, will return nullptr
	*/
	template <>
	std::shared_ptr<dynamic_lights> content_manager::get(const std::string& name)
	{
		// Try and get dynamic lights
		auto found = _dynamic_lights.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _dynamic_lights.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a shader from the content manager.  If shader doesn't exist, will return
	nullptr
	*/
	template <>
	std::shared_ptr<shader> content_manager::get(const std::string& name)
	{
		// Try and get shader
		auto found = _shaders.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _shaders.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets an effect from the content manager.  If effect doesn't exist, will 
	return nullptr
	*/
	template <>
	std::shared_ptr<effect> content_manager::get(const std::string& name)
	{
		// Try and get effect
		auto found = _effects.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _effects.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a frame buffer from the content manager.  If frame buffer doesn't
	exist, will return nullptr
	*/
	template <>
	std::shared_ptr<frame_buffer> content_manager::get(const std::string& name)
	{
		// Try and find frame buffer
		auto found = _frame_buffers.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _frame_buffers.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a depth buffer from the content manager.  If depth buffer doesn't
	exist, will return nullptr
	*/
	template <>
	std::shared_ptr<depth_buffer> content_manager::get(const std::string& name)
	{
		// Try and find depth buffer
		auto found = _depth_buffers.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _depth_buffers.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a shadow map from the content manager.  If shadow map doesn't 
	exist, will return nullptr
	*/
	template <>
	std::shared_ptr<shadow_map> content_manager::get(const std::string& name)
	{
		// Try and find shadow map
		auto found = _shadow_maps.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _shadow_maps.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a render pass from the content manager.  If render pass doesn't exist
	will return nullptr
	*/
	template <>
	std::shared_ptr<render_pass> content_manager::get(const std::string& name)
	{
		// Try and find render pass
		auto found = _render_passes.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _render_passes.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Gets a frame buffer from the content manager.  If post process doesn't exist
	will return nullptr
	*/
	template <>
	std::shared_ptr<post_process> content_manager::get(const std::string& name)
	{
		// Try and get post process
		auto found = _post_processes.find(name);
		// If found, return value.  Otherwise return nullptr
		if (found != _post_processes.end())
			return found->second;
		else
			return nullptr;
	}

	/*
	Loads a piece of geometry from a file.  Essentially treats a model as simple
	geometry.  Also adds to content manager store
	*/
	template <>
	std::shared_ptr<geometry>  content_manager::load(const std::string& filename)
	{
		// First check if model geometry already loaded.  If so, return already
		// loaded value
		auto found = _geometry.find(filename);
		if (found != _geometry.end())
		{
			// Display message and return true
			std::clog << "Geometry " << filename << " already loaded" << std::endl;
			return found->second;
		}
		// Try and load model via model loader
		auto value = model_loader::load<geometry>(filename);
		if (value != nullptr)
			// Model loaded successfully.  Add to content manager
			_geometry[filename] = value;

		// Now just return the value.  If it is a nullptr, caller has to deal with it
		return value;
	}

	/*
	Loads a model from a file.  Also adds to content manager store
	*/
	template <>
	std::shared_ptr<model> content_manager::load(const std::string& filename)
	{
		// First check if model already loaded.  If so, return already loaded
		// value
		auto found = _models.find(filename);
		if (found != _models.end())
		{
			// Display message and return true
			std::clog << "Model " << filename << " already loaded" << std::endl;
			return found->second;
		}
		// Try and load model via model loader
		auto value = model_loader::load<model>(filename);
		if (value != nullptr)
			// Model loaded successfully.  Add to content manager
			_models[filename] = value;

		// Now just return the value.  If it is a nullptr, caller has to deal with it
		return value;
	}

	/*
	Loads a texture from a file.  Also adds to content manager store
	*/
	template <>
	std::shared_ptr<texture> content_manager::load(const std::string& filename)
	{
		// First check if texture already loaded.  If so, return already loaded
		// value
		auto found = _textures.find(filename);
		if (found != _textures.end())
		{
			// Display message and return true
			std::clog << "Texture " << filename << " already loaded" << std::endl;
			return found->second;
		}
		// Try and load texture via texture loader
		auto value = texture_loader::load(filename);
		if (value != nullptr)
			// Texture loaded successfully.  Add to content manager
			_textures[filename] = value;
		
		// Return value.  Caller will deal with if nullptr
		return value;
	}

	/*
	Loads a piece of terrain from a texture file.  Also adds to content manager
	store
	*/
	template <>
	std::shared_ptr<terrain> content_manager::load(const std::string& filename)
	{
		// First check if terrain already loaded.  If so, return already loaded
		// value
		auto found = _terrain.find(filename);
		if (found != _terrain.end())
		{
			// Display message and return true
			std::clog << "Terrain " << filename << " already loaded" << std::endl;
			return found->second;
		}
		// Try and load terrain via terrain loader
		auto value = terrain_loader::load(filename);
		if (value != nullptr)
			// Terrain loaded successfully.  Add to content manager
			_terrain[filename] = value;
		// Return loaded terrain.  nullptr dealt with by caller
		return value;
	}

	/*
	Loads a shader from a file.  Also adds to content manager
	*/
	std::shared_ptr<shader> content_manager::load(const std::string& filename, GLenum type)
	{
		// First check if shader already loaded.  If so, return already loaded
		// value
		auto found = _shaders.find(filename);
		if (found != _shaders.end())
		{
			// Display message and return true
			std::clog << "Shader " << filename << " already loaded" << std::endl;
			return found->second;
		}
		auto value = effect_loader::load_shader(filename, type);
		// Try and load shader via shader loader
		if (value != nullptr)
		{
			// Shader loaded successfully.  Add to content manager
			_shaders[filename] = value;
			return value;
		}
		else
			// Not loaded.  Return nullptr
			return nullptr;
	}

	/*
	Builds a cube map.  Will also add to the content manager
	*/
	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<cube_map>& value)
	{
		// First check if cube map of given name already exists.
		auto found = _cube_maps.find(name);
		if (found != _cube_maps.end())
		{
			// Cube map of given name already exists.  Display error and return
			// false
			std::cerr << "Error: cube map " << name << " already exists" << std::endl;
			return false;
		}
		// Try and load cube map via texture loader
		value = texture_loader::load(value->filenames);
		if (value != nullptr)
		{
			// Cube maps built successfully.  Add to content manager
			_cube_maps[name] = value;
			return true;
		}
		else
			// Not loaded.  Return false
			return false;
	}

	/*
	Builds a skybox.  Will also add to the content manager
	*/
	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<skybox>& value)
	{
		// First check if skybox of given name already exists.
		auto found = _skyboxes.find(name);
		if (found != _skyboxes.end())
		{
			// Skybox of given name already exists.  Display error and return
			// false
			std::cerr << "Error: skybox " << name << " already exists" << std::endl;
			return false;
		}

		// Check if effect has been built
		if (value->eff == 0 || value->eff->program == 0)
		{
			// Effect not built.  Display error and return false
			std::cerr << "Error: could not build skybox " << name << std::endl;
			std::cerr << "Effect not built" << std::endl;
			return false;
		}

		// Try and load cube map
		value->tex = texture_loader::load(value->tex->filenames);
		if (value->tex == nullptr)
			// Cube map not loaded.  Return false
			return false;

		// Cube map loaded.  Check if geometry loaded
		if (value->geom == nullptr || value->geom->vertex_array_object == 0)
			// Set geometry to default skybox geometry
			value->geom = _geometry["skybox"];
		else
			// Add geometry to content manager
			_geometry[(name + "_geom")] = value->geom;

		// Skybox is now built.  Add to content manager
		// First add cube map
		_cube_maps[(name + "_cm")] = value->tex;

		// Add skybox to content manager
		_skyboxes[name] = value;

		return true;
	}

	/*
	Builds a piece of terrain.  Will also add to the content manager
	*/
	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<terrain>& value)
	{
		// First check if terrain already exists in content manager
		auto found = _terrain.find(name);
		if (found != _terrain.end())
		{
			// Terrain of given name already exists.  Display error and return
			// false
			std::cerr << "Terrain " << name << " already exists" << std::endl;
			return false;
		}

		// TODO - build terrain?
		return false;
	}

	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<mesh>& value)
	{
		 // TODO - build mesh
		return false;
	}

	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<directional_light>& value)
	{
		// TODO - build directional light
		return false;
	}

	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<point_light>& value)
	{
		// TODO
		return false;
	}

	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<spot_light>& value)
	{
		// TODO
		return false;
	}

	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<dynamic_lights>& value)
	{
		// TODO
		return false;
	}

	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<effect>& value)
	{
		// TODO
		return false;
	}

	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<frame_buffer>& value)
	{
		// TODO
		// TODO - building SCREEN?
		_frame_buffers[name] = value;
		return false;
	}

	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<depth_buffer>& value)
	{
		// TODO
		return false;
	}

	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<shadow_map>& value)
	{
		// TODO
		return false;
	}

	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<render_pass>& value)
	{
		// TODO
		return false;
	}

	template <>
	bool content_manager::build(const std::string& name, std::shared_ptr<post_process>& value)
	{
		// TODO
		return false;
	}

	/*
	Adds a piece of geometry to the content manager.  Will check if content is
	built, and if not will build it.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<geometry>& value)
	{
		// First, check if geometry of given name exists in the content manager
		auto found = _geometry.find(name);
		if (found != _geometry.end())
		{
			// Geometry already exists in the content manager.  Display message
			// and return false
			std::cerr << "Error: geometry " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Geometry does not exist.  Check if built
			if (value->vertex_array_object == 0)
				// Geometry not built (vertex array is 0).  Build.
				if (!geometry_builder::initialise_geometry(value))
					// Geometry not built.  Return false
					return false;

			// Geometry is successfully built, and name doesn't exist in 
			// content manager.  Add to content manager
			_geometry[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a model to the content manager.  Will check if model has been loaded, 
	and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<model>& value)
	{
		// First check if model of given name exists in content manager
		auto found = _models.find(name);
		if (found != _models.end())
		{
			// Model already exists in the content manager.  Display message
			// and return false
			std::cerr << "Error: model " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Model does not exist.  Check if loaded
			if (value->geometry->vertex_array_object == 0)
			{
				// This is the only check we have at the moment.  It will do
				// Assume name is a filename.  Try and load model
				value = model_loader::load<model>(name);
				if (value == nullptr)
					// Model not loaded.  Return false
					return false;
			}

			// Model is successfully loaded and does not exist in the content
			// manager.  Add to content manager
			_models[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a texture to the content manager.  Will check if the texture has been
	loaded, and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<texture>& value)
	{
		// First check if texture of given name exists in content manager
		auto found = _textures.find(name);
		if (found != _textures.end())
		{
			// Texture already exists in the content manager.  Display message 
			// and return false
			std::cerr << "Error: texture " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Texture does not exist.  Check if loaded
			if (value->image == 0)
			{
				// Image ID in OpenGL is 0 (no image).  Use name as filename
				// to load image
				value = texture_loader::load(name);
				if (value == nullptr)
					// Texture not loaded.  Return false
					return false;
			}

			// Texture is already loaded and does not exist in the content
			// manager.  Add to content manager
			_textures[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a cube map to the content manager.  Will check if the cube map has been
	loaded, and if not will do so
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<cube_map>& value)
	{
		// First check if cube map of given name exists in content manager
		auto found = _cube_maps.find(name);
		if (found != _cube_maps.end())
		{
			// Cube map already exists in the content manager.  Display message
			// and return false
			std::cerr << "Error: cube map " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Cube map does not exist.  Check if loaded
			if (value->image == 0)
				// Image ID in OpenGL is 0 (no image).  Try and build
				return build(name, value);

			// Cube map is successfully loaded and does not exist in the content
			// manager.  Add to content manager
			_cube_maps[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a skybox to the content manager.  Will check if the skybox has been built
	and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<skybox>& value)
	{
		// First check if skybox of given name exists in content manager
		auto found = _skyboxes.find(name);
		if (found != _skyboxes.end())
		{
			// Skybox already exists in the content manager.  Display message
			// and return false
			std::cerr << "Error: skybox " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Skybox does not exist.  Check if built
			if (value->tex->image == 0)
				// Image ID in OpenGL is 0 (no image).  Try and build.  Return
				// result of build
				return build(name, value);

			// Skybox is successfully built and is not in content manager.  Add
			// to content manager
			_skyboxes[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a piece of terrain to the content manager.  Will check if the terrain 
	has been built, and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<terrain>& value)
	{
		// First check if terrain of given name exists in content manager
		auto found = _terrain.find(name);
		if (found != _terrain.end())
		{
			// Terrain already exists in the content manager.  Display message
			// and return false
			std::cerr << "Error: terrain " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Terrain does not exist.  Check if loaded
			if (value->geom->positions.size() == 0)
			{
				// Terrain is not loaded.  Load terrain assuming name is 
				// is filename
				value = terrain_loader::load(name);
				if (value == nullptr)
					// Terrain not loaded.  Return false
					return false;
			}
			// Geometry data exists, but is it built?
			else if (value->geom->vertex_array_object == 0)
				// Vertex array is 0 (no array).  Try and build
				if (!geometry_builder::initialise_geometry(value->geom))
					// Geometry not initialise.  Return false
					return false;

			// Now check if material is initialised
			if (value->mat->buffer == 0)
				// Material data is not built.  Build material, using name of 
				// terrain
				if (!build((name + "_mat"), value->mat))
					// Material not built.  Return false
					return false;

			// Terrain is successfully loaded / built, but not in content manager.
			// Add to content manager.
			_terrain[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a material to the content manager.  Will check if the material has been
	built, and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<material>& value)
	{
		// First check if material of given name already exists
		auto found = _materials.find(name);
		if (found != _materials.end())
		{
			// Material already exists in content manager.  Display message
			// and return false
			std::cerr << "Error: material " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Material doesn't exist.  Check if built
			if (value->buffer == 0)
				// Material data not built.  Try and build.  Return result of
				// build
				return build(name, value);

			// Material is already built but not in content manager.  Add to
			// the content manager.
			_materials[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a mesh to the content manager.  Will check if the relevant
	content has been loaded / built, and if not will do so
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<mesh>& value)
	{
		// First check if mesh of given name already exists
		auto found = _meshes.find(name);
		if (found != _meshes.end())
		{
			// Mesh already exists in content manager.  Display message
			// and return false
			std::cerr << "Error: mesh " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Mesh doesn't exist.  Check if built
			if (value->geom->vertex_array_object == 0 || value->mat->buffer == 0)
				// We check bot the vertex array and material buffer for 
				// for initialisation.  Either one being 0 (not built) will 
				// cause a build operation.  Return result from build
				return build(name, value);

			// Mesh already built and not in content manager.  Add to
			// the content manager
			_meshes[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a directional light to the content manager.  Will check if the light
	has been built, and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<directional_light>& value)
	{
		// First check if light of given name exists in content manager
		auto found = _directional_lights.find(name);
		if (found != _directional_lights.end())
		{
			// Directional light of given name already exists.  Display error
			// and return false
			std::cerr << "Error: directional light " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Directional light doesn't exist.  Check if built
			if (value->buffer == 0)
				// Directional light not built.  Try and build.  Return result
				// from build
				return build(name, value);

			// Directional light built and not in content manager.  Add to the 
			// content manager
			_directional_lights[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a point light to the content manager.  Will check if the light has 
	been built, and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<point_light>& value)
	{
		// First check if point light of given name exists in content manager
		auto found = _point_lights.find(name);
		if (found != _point_lights.end())
		{
			// Point light of given name already exists.  Display error and 
			// return false
			std::cerr << "Error: point light " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Point light doesn't exist.  Check if built
			if (value->buffer == 0)
				// Point light not built.  Try and build.  Return result from
				// build
				return build(name, value);

			// Point light built and not in content manager.  Add to the content
			// manager
			_point_lights[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a spot light to the content manager.  Will check if the light has been
	built, and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<spot_light>& value)
	{
		// First check if spot light of given name exists in content manager
		auto found = _spot_lights.find(name);
		if (found != _spot_lights.end())
		{
			// Spot light of given name already exists.  Display error and return
			// false
			std::cerr << "Error: spot light " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Spot light doesn't exist.  Check if built
			if (value->buffer == 0)
				// Spot light not built.  Try and build.  Return result from
				// build
				return build(name, value);

			// Spot light built and not in content manager.  Add to the content 
			// manager
			_spot_lights[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a set of dynamic lights to the content manager.  Will check if the 
	light has been built, and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<dynamic_lights>& value)
	{
		// First check if dynamic lights of the given name exists in the content
		// manager.
		auto found = _dynamic_lights.find(name);
		if (found != _dynamic_lights.end())
		{
			// Dynamic lights of given name already exists.  Display error and 
			// return false
			std::cerr << "Error: dynamic lights " << name << " << already exists" << std::endl;
			return false;
		}
		else
		{
			// Dynamic lights do not exist in content manager.  Check if built
			if (value->buffer == 0)
				// Dynamic lights not built.  Try and build.  Return result from
				// build
				return build(name, value);

			// Dynamic lights built and not in content manager.  Add to the
			// content manager
			_dynamic_lights[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a shader to the content manager.  Will check if the shader has been
	loaded, and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<shader>& value)
	{
		// Check if shader of given name exists in the content manager
		auto found = _shaders.find(name);
		if (found != _shaders.end())
		{
			// Shader of given name already exists.  Display error and return
			// false
			std::cerr << "Error: shader " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Shader does not exist in content manager.  Check if loaded
			if (value->id == 0)
			{
				// Shader not loaded.  Assume name is filename.  Try and load.
				// Return result from load
				value = load(name, value->type);
				return (value != nullptr);
			}

			// Shader loaded and not in content manager.  Add to the content 
			// manager
			_shaders[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds an effect to the content manager.  Will check if the effect has been
	built, and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<effect>& value)
	{
		// Check if effect of given name exists in the content manager
		auto found = _effects.find(name);
		if (found != _effects.end())
		{
			// Effect of given name already exists.  Display error and return
			// false
			std::cerr << "Error: effect " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Effect does not exist in content manager.  Check if built
			if (value->program == 0)
			{
				// Effect not built.  Try and build
				return build(name, value);
			}

			// Effect is built but not in content manager.  Add to the content
			// manager
			_effects[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a frame buffer to the content manager.  Will check if the frame buffer
	has been built, and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<frame_buffer>& value)
	{
		// Check if frame buffer of given name exists in the content manager
		auto found = _frame_buffers.find(name);
		if (found != _frame_buffers.end())
		{
			// Frame buffer of given name already exists.  Display error and
			// return false
			std::cerr << "Error: frame buffer " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Frame buffer does not exist.  Check if built
			if (value->buffer == 0)
				// Frame buffer not built.  Try and build.  Return result of
				// build operation
				return build(name, value);

			// Frame buffer built.  Add to content manager
			_frame_buffers[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a depth buffer to the content manager.  Will check if the depth buffer
	has been built, and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<depth_buffer>& value)
	{
		// Check if depth buffer of given name exists in the content manager
		auto found = _depth_buffers.find(name);
		if (found != _depth_buffers.end())
		{
			// Depth buffer of given name already exists.  Display error and
			// return false
			std::cerr << "Error: depth buffer " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Depth buffer does not exist.  Check if built
			if (value->buffer == 0)
				// Depth buffer not built.  Try and build.  Return result of
				// build operation
				return build(name, value);

			// Depth buffer built.  Add to content manager
			_depth_buffers[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a shadow map to the content manager.  Will check if the shadow map has
	been built, and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<shadow_map>& value)
	{
		// Check if shadow map of given name exists in the content manager
		auto found = _shadow_maps.find(name);
		if (found != _shadow_maps.end())
		{
			// Shadow map of given name already exists.  Display error and
			// return false
			std::cerr << "Error: shadow map " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Shadow map does not exist.  Check if built
			if (value->buffer == 0 || value->buffer->buffer == 0)
				// Depth buffer not built.  Try and build.  Return result of
				// build operation
				return build(name, value);

			// Shadow map built.  Add to content manager
			_shadow_maps[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a render pass to the content manager.  Will check if the render pass
	has been built, and if not will do so
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<render_pass>& value)
	{
		// Check if render pass of given name exists in the content manager
		auto found = _render_passes.find(name);
		if (found != _render_passes.end())
		{
			// Render pass of given name already exists.  Display error and 
			// return false
			std::cerr << "Error: render pass " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Render pass does not exist.  Check if built
			if (value->buffer == 0 || value->buffer->buffer == 0)
				// Render pass not built.  Try and build.  Return result of
				// build operation
				return build(name, value);

			// Render pass built.  Add to content manager
			_render_passes[name] = value;

			// Return true
			return true;
		}
	}

	/*
	Adds a post process to the content manager.  Will check if the post process
	has been built, and if not will do so.
	*/
	template <>
	bool content_manager::add(const std::string& name, std::shared_ptr<post_process>& value)
	{
		// Check if post proess of given name exists in the content manager
		auto found = _post_processes.find(name);
		if (found != _post_processes.end())
		{
			// Post process of given name already exists.  Display error and
			// return false
			std::cerr << "Error: post process " << name << " already exists" << std::endl;
			return false;
		}
		else
		{
			// Try and build.  Return result.  If already built, will be true anyway
			return build(name, value);
		}
	}
}