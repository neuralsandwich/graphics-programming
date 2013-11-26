#pragma once

#include <string>
#include <memory>

namespace render_framework
{
	// Forward declarations
	struct geometry;

	/*
	Data structure representing a loaded model
	*/
	struct model
	{
		// Placeholder.  Likely there will be geometry here
		std::shared_ptr<geometry> geometry;
	};

	/*
	Helper class used to load in a model
	*/
	class model_loader
	{
	public:
		// Loads in model data
		template <typename T>
		static std::shared_ptr<T> load(const std::string& filename);
	};

	template <typename T>
	std::shared_ptr<T> model_loader::load(const std::string& filename)
	{
		// Type is unknown.  Print an error accordingly.
		std::cerr << "Error trying to load model data into unknown type" << std::endl;
		std::cerr << "Type of: " << typeid(T).name() << std::endl;
		return nullptr;
	}

	extern template
		std::shared_ptr<model> model_loader::load(const std::string& filename);

	extern template
		std::shared_ptr<geometry> model_loader::load(const std::string& filename);
}