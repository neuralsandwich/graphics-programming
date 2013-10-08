#pragma once

#include "transform.h"

namespace render_framework
{
	// Forward declarations required for the render object
	struct geometry;
	struct material;

	/*
	A data structure used to represent a rendererable object
	*/
	struct mesh
	{
		// The world transform of the render object
		transform trans;
		// The geometry used by the render object
		std::shared_ptr<geometry> geom;
		// Material associated with the render object
		std::shared_ptr<material> mat;

		/*
		Constructs a new mesh.  Sets values accordingly
		*/
		mesh() : geom(nullptr), mat(nullptr)
		{
		}

		/*
		Destroys a mesh.
		*/
		~mesh()
		{
			// Reference counting on shared pointers should handle this
		}
	};
}