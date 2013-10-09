#pragma once

#include <string>
#include <unordered_map>
#include <glm\glm.hpp>
#include <boost\property_tree\json_parser.hpp>

#include "geometry.h"
#include "material.h"
#include "mesh.h"
#include "light.h"
#include "texture.h"
#include "model.h"
#include "terrain.h"
#include "skybox.h"
#include "effect.h"

namespace render_framework
{
	/*
	Data used to represent a scene
	*/
	struct scene_data
	{
		// Scene name
		std::string name;
		// Geometry
		std::unordered_map<std::string, std::shared_ptr<geometry>> geometry;
		// Meshes
		std::unordered_map<std::string, std::shared_ptr<mesh>> meshes;
		// Shaders
		std::unordered_map<std::string, std::shared_ptr<shader>> shaders;
		// Effects
		std::unordered_map<std::string, std::shared_ptr<effect>> effects;
		// Materials
		std::unordered_map<std::string, std::shared_ptr<material>> materials;
		// Scene light
		std::shared_ptr<directional_light> scene_light;
		// Lights
		std::shared_ptr<dynamic_lights> lights;
		// Textures
		std::unordered_map<std::string, std::shared_ptr<texture>> textures;
	};

	/*
	Helper class with utility methods to load scene data from JSON file
	*/
	class scene_loader
	{
	private:
		// Reads a vec2 from the scene file tree
		static glm::vec2 read_vec2(const boost::property_tree::ptree& pt);
		// Reads a vec3 from the scene file tree
		static glm::vec3 read_vec3(const boost::property_tree::ptree& pt);
		// Reads a vec4 from the scene file tree
		static glm::vec4 read_vec4(const boost::property_tree::ptree& pt);
		// Reads geometry from the scene file tree
		static void read_geometry(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads materials from the scene file
		static void read_materials(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads a transform from the scene file into a render object
		static void read_transform(std::shared_ptr<mesh> mesh, const boost::property_tree::ptree& pt);
		// Reads meshes from the scene file
		static void read_meshes(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads lighting from the scene file
		static void read_lighting(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads point light data from the scene file
		static void read_point_light(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads spot light data from the scene file
		static void read_spot_light(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads dynamic light data from the scene file
		static void read_dynamic_lights(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads textures from the scene file
		static void read_textures(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads procedural textures from the scene file
		static void read_prodedural_textures(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads models from the scene file
		static void read_models(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads terrain from the scene file
		static void read_terrain(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads shaders from the scene file
		static void read_shaders(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads effects from the scene file
		static void read_effects(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads render passes from the scene file
		static void read_render_passes(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads post processes from the scene file
		static void read_post_processes(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
		// Reads cube maps from the scene file
		static void read_cube_maps(std::shared_ptr<scene_data> data, const boost::property_tree::ptree& pt);
	public:
		// Loads a scene from the given scene file
		static std::shared_ptr<scene_data> load_scene(const std::string& filename);
	};

	/*
	Manages scenes, allowing adding, removing, loading and unloading.
	This class is a singleton and cannot be created by users.
	*/
	class scene_manager
	{
	private:
		// Map of scenes stored against names.  If using files, filename
		// defaults to scene name
		std::unordered_map<std::string, std::shared_ptr<scene_data>> _scenes;
		// Currently loaded scene
		std::shared_ptr<scene_data> _current;
		// Private constructor
		scene_manager() { }
		// Private copy constructor
		scene_manager(const scene_manager&) { }
		// Private assignment operator
		void operator=(scene_manager&) { }
	public:
		// Gets the singleton instance of the scene manager
		static scene_manager& get_instance()
		{
			// Created static instance
			static scene_manager instance;
			// Simply return created satic instance
			return instance;
		}
		// scene_manager destructor.  Cleans up all scene data
		~scene_manager();
		// Adds a scene to the scene manager by loading it in from a file
		bool add_scene(const std::string& filename);
		// Adds a scene to the scene manager
		bool add_scene(const std::string& name, std::shared_ptr<scene_data> scene);
		// Removes a scene from the scene manager
		bool remove_scene(const std::string& name);
		// Loads a scene into memory
		bool load_scene(const std::string& name);
		// Unloads a scene from memory
		bool unload_scene(const std::string& name);
		// Gets a scene from the scene manager
		std::shared_ptr<scene_data> get_scene(const std::string& name) const;
		// Gets the currently loaded scene from the scene manager
		std::shared_ptr<scene_data> get_current() const;
	};
}