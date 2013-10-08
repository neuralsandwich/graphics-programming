#pragma once

namespace render_framework
{
	// Forward declarations
	struct cube_map;
	struct geometry;
	struct effect;

	// Structure representing a skybox in the scene
	struct skybox
	{
		// Texture used by the sky box
		std::shared_ptr<cube_map> tex;
		// Geometry used by the sky box
		std::shared_ptr<geometry> geom;
		// Effect used by the sky box
		std::shared_ptr<effect> eff;
	};
}