#pragma once

#include <string>
#include <memory>

namespace render_framework
{
	// Declaration of texture struct.  Used in terrain loader
	struct texture;

	// Declaration of geometry struct.
	struct geometry;

	// Declaration of material struct
	struct material;

	/*
	A structure that represents terrain
	*/
	struct terrain
	{
		// Geometry used by the terrain
		std::shared_ptr<geometry> geom;
		// Material used by the terrain
		std::shared_ptr<material> mat;
	};

	/*
	Helper class that loads in terrain from a file
	*/
	class terrain_loader
	{
	public:
		// Loads terrain from a given file
		static std::shared_ptr<terrain> load(const std::string& filename);
		// Builds terrain from a given texture
		static std::shared_ptr<terrain> build(std::shared_ptr<texture> tex);
	};

	/*
	Helper class to generate terrain from a given noise function
	*/
	class terrain_generator
	{
	public:
		static std::shared_ptr<terrain> generate(/*TODO noise*/);
	};
}