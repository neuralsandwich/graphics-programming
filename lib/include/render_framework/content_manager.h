#pragma once

#include <string>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <GL\glew.h>

namespace render_framework
{
	// Declare data structures in use.  Don't define these here - done elsewhere

	// Declarations for geometry type objects
	struct geometry;
	struct model;

	// Declarations for texture like objects
	struct texture;
	struct cube_map;
	struct skybox;

	// Declaration for terrain
	struct terrain;

	// Declaration for material
	struct material;

	// Declaration for mesh
	struct mesh;

	// Declarations for lighting
	struct directional_light;
	struct point_light;
	struct spot_light;
	struct dynamic_lights;

	// Declarations for effects
	struct shader;
	struct effect;

	// Declarations for frame buffer type objects
	struct frame_buffer;
	struct depth_buffer;
	struct shadow_map;

	// Declarations for render passes and post processes
	struct render_pass;
	struct post_process;

	/*
	Class responsible for loading, building and managing content.  Singleton
	instance as we only want one content manager in our system.  Generally,
	content should be handled via the content manager, although it is possible
	to build and load content directly if desired.
	*/
	class content_manager
	{
	private:
		// Data store for all currently loaded geometry
		std::unordered_map<std::string, std::shared_ptr<geometry>> _geometry;

		// Data store for all currently loaded models
		std::unordered_map<std::string, std::shared_ptr<model>> _models;

		// Data store for all currently loaded textures
		std::unordered_map<std::string, std::shared_ptr<texture>> _textures;

		// Data store for all currently loaded cube maps
		std::unordered_map<std::string, std::shared_ptr<cube_map>> _cube_maps;

		// Data store for all currently built sky boxes
		std::unordered_map<std::string, std::shared_ptr<skybox>> _skyboxes;

		// Data store for all currently built terrain
		std::unordered_map<std::string, std::shared_ptr<terrain>> _terrain;

		// Data store for all currently built materials
		std::unordered_map<std::string, std::shared_ptr<material>> _materials;

		// Data store for all currently built meshes
		std::unordered_map<std::string, std::shared_ptr<mesh>> _meshes;

		// Data store for all currently built directional lights
		std::unordered_map<std::string, std::shared_ptr<directional_light>> _directional_lights;

		// Data store for all currently built point lights
		std::unordered_map<std::string, std::shared_ptr<point_light>> _point_lights;

		// Data store for all currently built spot lights
		std::unordered_map<std::string, std::shared_ptr<spot_light>> _spot_lights;

		// Data store for all currently built dynamic lights
		std::unordered_map<std::string, std::shared_ptr<dynamic_lights>> _dynamic_lights;

		// Data store for all currently loaded shaders
		std::unordered_map<std::string, std::shared_ptr<shader>> _shaders;

		// Data store for all currently built effects
		std::unordered_map<std::string, std::shared_ptr<effect>> _effects;

		// Data store for all currently built frame buffers
		std::unordered_map<std::string, std::shared_ptr<frame_buffer>> _frame_buffers;

		// Data store for all currently built depth buffers
		std::unordered_map<std::string, std::shared_ptr<depth_buffer>> _depth_buffers;

		// Data store for all currently built shadow maps
		std::unordered_map<std::string, std::shared_ptr<shadow_map>> _shadow_maps;

		// Data store for all currently built render passes
		std::unordered_map<std::string, std::shared_ptr<render_pass>> _render_passes;

		// Data store for all currently built post processes
		std::unordered_map<std::string, std::shared_ptr<post_process>> _post_processes;

		// Private construtor.  This is a singleton
		content_manager() { }

		// Private copy constructor
		content_manager(const content_manager&) { }

		// Private assignment operator
		void operator=(content_manager&) { }

	public:
		// Destructor.  Must ensure that all content is unloaded
		~content_manager() { unload_content(); }

		// Gets the singleton instance of the content manager
		static content_manager& get_instance()
		{
			// Static instance.  Only one ever created.
			static content_manager manager;
			// Return the static instance
			return manager;
		}

		// Unloads content in the content manager.
		void unload_content();

		// Adds a piece of content to the content manager.  Used when individual
		// content creators are used rather than using content manager directly
		template <typename T>
		bool add(const std::string& name, std::shared_ptr<T>& value);

		// Gets a piece of content stored in the content manager
		template <typename T>
		std::shared_ptr<T> get(const std::string& name);

		// Loads content into the content manager.  Filename is used as the 
		// storage key
		template <typename T>
		std::shared_ptr<T> load(const std::string& filename);

		// Loads a shader into the content manager.  Type of shader is required,
		// hence a unique method
		std::shared_ptr<shader> load(const std::string& filename, GLenum type);

		// Builds content and stores in the content manager
		template <typename T>
		bool build(const std::string& name, std::shared_ptr<T>& value);
	};

	/*
	Default add content method.  This method will only be called if an attempt
	is made to add an unknown type to the content manager.  Will print an error
	accordingly
	*/
	template <typename T>
	bool content_manager::add(const std::string& name, std::shared_ptr<T>& value)
	{
		// Type is unknown.  Print an error accordingly
		std::cerr << "Attempting to add object to content manager of unknown type" << std::endl;
		std::cerr << "Type of: " << typeid(T).name() << std::endl;
		return false;
	}

	/*
	Adds a piece of geometry to the content manager.  Will check if the geometry
	has been built, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<geometry>& value);

	/*
	Adds a model to the content manager.  Will check if model has been loaded, 
	and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<model>& value);

	/*
	Adds a texture to the content manager.  Will check if the texture has been
	loaded, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<texture>& value);

	/*
	Adds a cube map to the content manager.  Will check if the cube map has been
	loaded, and if not will do so
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<cube_map>& value);

	/*
	Adds a skybox to the content manager.  Will check if the skybox has been built
	and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<skybox>& value);

	/*
	Adds a piece of terrain to the content manager.  Will check if the terrain 
	has been built, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<terrain>& value);

	/*
	Adds a material to the content manager.  Will check if the material has been
	built, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<material>& value);

	/*
	Adds a mesh to the content manager.  Will check if the relevant
	content has been loaded / built, and if not will do so
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<mesh>& value);

	/*
	Adds a directional light to the content manager.  Will check if the light
	has been built, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<directional_light>& value);

	/*
	Adds a point light to the content manager.  Will check if the light has 
	been built, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<point_light>& value);

	/*
	Adds a spot light to the content manager.  Will check if the light has been
	built, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<spot_light>& value);

	/*
	Adds a set of dynamic lights to the content manager.  Will check if the 
	light has been built, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<dynamic_lights>& value);

	/*
	Adds a shader to the content manager.  Will check if the shader has been
	loaded, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<shader>& value);

	/*
	Adds an effect to the content manager.  Will check if the effect has been
	built, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<effect>& value);

	/*
	Adds a frame buffer to the content manager.  Will check if the frame buffer
	has been built, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<frame_buffer>& value);

	/*
	Adds a depth buffer to the content manager.  Will check if the depth buffer
	has been built, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<depth_buffer>& value);

	/*
	Adds a shadow map to the content manager.  Will check if the shadow map has
	been built, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<shadow_map>& value);

	/*
	Adds a render pass to the content manager.  Will check if the render pass
	has been built, and if not will do so
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<render_pass>& value);

	/*
	Adds a post process to the content manager.  Will check if the post process
	has been built, and if not will do so.
	*/
	extern template
	bool content_manager::add(const std::string& name, std::shared_ptr<post_process>& value);

	/*
	Default get method of the content manager.  This is called when an attempt
	to get a type not managed by the content manager is performed.  Will print
	an error accordingly.
	*/
	template <typename T>
	std::shared_ptr<T> content_manager::get(const std::string& name)
	{
		// Type is unknown.  Print an error accordingly.
		std::cerr << "Error trying to get object from content manager of unknown type" << std::endl;
		std::cerr << "Type of: " << typeid(T).name() << std::endl;
		return nullptr;
	}

	/*
	Gets a piece of geometry from the content manager.  If geometry doesn't 
	exist, will return nullptr
	*/
	extern template
	std::shared_ptr<geometry> content_manager::get(const std::string& name);

	/*
	Gets a model from the content manager.  If model doesn't exist, will return
	nullptr
	*/
	extern template
	std::shared_ptr<model> content_manager::get(const std::string& name);

	/*
	Gets a texture from the content manager.  If texture doesn't exist, will 
	return nullptr
	*/
	extern template
	std::shared_ptr<texture> content_manager::get(const std::string& name);

	/*
	Gets a cube map from the content manager.  If cube map doesn't exist, will
	return nullptr
	*/
	extern template
	std::shared_ptr<cube_map> content_manager::get(const std::string& name);

	/*
	Gets a skybox from the content manager.  If sky box doesn't exist, will
	return nullptr
	*/
	extern template
	std::shared_ptr<skybox> content_manager::get(const std::string& name);

	/*
	Gets a piece of terrain from the content manager.  If terrain doesn't exist,
	will return nullptr
	*/
	extern template
	std::shared_ptr<terrain> content_manager::get(const std::string& name);

	/*
	Gets a material from the content manager.  If material doesn't exist, will
	return nullptr
	*/
	extern template
	std::shared_ptr<material> content_manager::get(const std::string& name);

	/*
	Gets a mesh from the content manager.  If render object doesn't
	exist, will return nullptr
	*/
	extern template
	std::shared_ptr<mesh> content_manager::get(const std::string& name);

	/*
	Gets a directional light from the content manager.  If directional light
	doesn't exist, will return nullptr
	*/
	extern template
	std::shared_ptr<directional_light> content_manager::get(const std::string& name);

	/*
	Gets a point light from the content manager.  If point light doesn't exist,
	will return nullptr
	*/
	extern template
	std::shared_ptr<point_light> content_manager::get(const std::string& name);

	/*
	Gets a spot light from the content manager.  If spot light doesn't exist, 
	will return nullptr
	*/
	extern template
	std::shared_ptr<spot_light> content_manager::get(const std::string& name);

	/*
	Gets a set of dynamic lights from the content manager.  If light doesn't
	exist, will return nullptr
	*/
	extern template
	std::shared_ptr<dynamic_lights> content_manager::get(const std::string& name);

	/*
	Gets a shader from the content manager.  If shader doesn't exist, will return
	nullptr
	*/
	extern template
	std::shared_ptr<shader> content_manager::get(const std::string& name);

	/*
	Gets an effect from the content manager.  If effect doesn't exist, will 
	return nullptr
	*/
	extern template
	std::shared_ptr<effect> content_manager::get(const std::string& name);

	/*
	Gets a frame buffer from the content manager.  If frame buffer doesn't
	exist, will return nullptr
	*/
	extern template
	std::shared_ptr<frame_buffer> content_manager::get(const std::string& name);

	/*
	Gets a depth buffer from the content manager.  If depth buffer doesn't
	exist, will return nullptr
	*/
	extern template
	std::shared_ptr<depth_buffer> content_manager::get(const std::string& name);

	/*
	Gets a shadow map from the content manager.  If shadow map doesn't 
	exist, will return nullptr
	*/
	extern template
	std::shared_ptr<shadow_map> content_manager::get(const std::string& name);

	/*
	Gets a render pass from the content manager.  If render pass doesn't exist
	will return nullptr
	*/
	extern template
	std::shared_ptr<render_pass> content_manager::get(const std::string& name);

	/*
	Gets a frame buffer from the content manager.  If post process doesn't exist
	will return nullptr
	*/
	extern template
	std::shared_ptr<post_process> content_manager::get(const std::string& name);

	/*
	Default load method for the content manager.  Called when an attempt to
	load content of an unknown / incorrect type is made.  Will display an error
	message and return false.
	*/
	template <typename T>
	std::shared_ptr<T> content_manager::load(const std::string& name)
	{
		std::cerr << "Error trying to load content of unknown type" << std::endl;
		std::cerr << "Type of: " << typeid(T).name() << std::endl;
		return nullptr;
	}

	/*
	Loads a piece of geometry from a file.  Essentially treats a model as simple
	geometry.  Also adds to content manager store
	*/
	extern template
	std::shared_ptr<geometry> content_manager::load(const std::string& filename); 

	/*
	Loads a model from a file.  Also adds to content manager store
	*/
	extern template
	std::shared_ptr<model> content_manager::load(const std::string& filename);

	/*
	Loads a texture from a file.  Also adds to content manager store
	*/
	extern template
	std::shared_ptr<texture> content_manager::load(const std::string& filename);

	/*
	Loads a piece of terrain from a texture file.  Also adds to content manager
	store
	*/
	extern template
	std::shared_ptr<terrain> content_manager::load(const std::string& filename);

	/*
	Default method called for building on the content manager.  Is called attempted
	load type is unknown / incorrect.  Will display an error message and return
	false
	*/
	template <typename T>
	bool content_manager::build(const std::string& name, std::shared_ptr<T>& value)
	{
		std::cerr << "Error trying to build object of unknown type" << std::endl;
		std::cerr << "Type of: " << typeid(T).name() << std::endl;
		return false;
	}

	/*
	Builds a cube map.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<cube_map>& value);

	/*
	Builds a skybox.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<skybox>& value);

	/*
	Builds a piece of terrain.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<terrain>& value);

	/*
	Builds a mesh.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<mesh>& value);

	/*
	Builds a directional light.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<directional_light>& value);

	/*
	Builds a point light.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<point_light>& value);

	/*
	Builds a spot light.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<spot_light>& value);

	/*
	Builds a set of dynamic lights.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<dynamic_lights>& value);

	/*
	Builds an effect.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<effect>& value);

	/*
	Builds a frame buffer.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<frame_buffer>& value);

	/*
	Builds a depth buffer.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<depth_buffer>& value);

	/*
	Builds a shadow map.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<shadow_map>& value);

	/*
	Builds a render pass.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<render_pass>& value);

	/*
	Builds a post process.  Will also add to the content manager
	*/
	extern template
	bool content_manager::build(const std::string& name, std::shared_ptr<post_process>& value);
};