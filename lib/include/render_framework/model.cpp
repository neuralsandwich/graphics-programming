#include "model.h"
#include "geometry.h"

#include <memory>

namespace render_framework
{
	template <>
	std::shared_ptr<model> model_loader::load(const std::string& name)
	{
		return nullptr;
	}

	template <>
	std::shared_ptr<geometry> model_loader::load(const std::string& name)
	{
		return nullptr;
	}
}