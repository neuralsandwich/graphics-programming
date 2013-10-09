#pragma once

#include <vector>

namespace render_framework
{
	// Forward declarations
	struct frame_buffer;
	struct geometry;
	struct effect;

	/*
	Structure representing a render pass in the render framework
	*/
	struct render_pass
	{
		// Frame buffer to store render pass information in
		std::shared_ptr<frame_buffer> buffer;
		// Effect used in the render pass
		std::shared_ptr<effect> eff;
	};

	/*
	Structure representing a post process in the render framework
	*/
	struct post_process
	{
		// Vector of render passes used in the post process
		std::vector<std::shared_ptr<render_pass>> passes;
		// Screen space quad to render to
		std::shared_ptr<geometry> screen_quad;
	};
}