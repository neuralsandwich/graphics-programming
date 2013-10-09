#include "terrain.h"

#include <memory>

namespace render_framework
{
	std::shared_ptr<terrain> terrain_loader::load(const std::string& filename)
	{
		return nullptr;
	}

	std::shared_ptr<terrain> terrain_loader::build(std::shared_ptr<texture> tex)
	{
		return nullptr;
	}

	std::shared_ptr<terrain> terrain_generator::generate()
	{
		return nullptr;
	}
}