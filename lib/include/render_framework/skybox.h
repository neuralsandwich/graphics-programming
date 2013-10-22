#pragma once

namespace render_framework
{
	// Forward declarations
	struct cube_map;
	struct effect;

	// Structure representing a skybox in the scene
	struct skybox
	{
		// Texture used by the sky box
		std::shared_ptr<cube_map> tex;
		// Effect used by the sky box
		std::shared_ptr<effect> eff;
	};
}