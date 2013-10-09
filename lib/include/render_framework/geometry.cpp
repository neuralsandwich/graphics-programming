#include "geometry.h"
#include <glm\gtx\norm.hpp>
#include <memory>
#include <array>

namespace render_framework
{
	// Initialises a piece of geometry
	bool geometry_builder::initialise_geometry(std::shared_ptr<geometry> geom)
	{
		// Generate and bind vertex array
		glGenVertexArrays(1, &geom->vertex_array_object);
		glBindVertexArray(geom->vertex_array_object);

		// If we have position data, then add to the vertex array object
		if (geom->positions.size() > 0)
		{
			// Generate buffer
			glGenBuffers(1, &geom->position_buffer);
			// Bind buffer
			glBindBuffer(GL_ARRAY_BUFFER, geom->position_buffer);
			// Set data for buffer
			glBufferData(GL_ARRAY_BUFFER, geom->positions.size() * sizeof(glm::vec3), &geom->positions[0], GL_STATIC_DRAW);
			// Enable attribute pointer for position data
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
		}

		// If we have normal data, then add to the vertex array object
		if (geom->normals.size() > 0)
		{
			// Generate buffer
			glGenBuffers(1, &geom->normal_buffer);
			// Bind buffer
			glBindBuffer(GL_ARRAY_BUFFER, geom->normal_buffer);
			// Set data for buffer
			glBufferData(GL_ARRAY_BUFFER, geom->normals.size() * sizeof(glm::vec3), &geom->normals[0], GL_STATIC_DRAW);
			// Enable attribute pointer for normal data
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);
		}

		// If we have texture data, then add to the vertex array object
		if (geom->tex_coords.size() > 0)
		{
			// Generate buffer
			glGenBuffers(1, &geom->tex_coord_buffer);
			// Bind buffer
			glBindBuffer(GL_ARRAY_BUFFER, geom->tex_coord_buffer);
			// Set data for buffer
			glBufferData(GL_ARRAY_BUFFER, geom->tex_coords.size() * sizeof(glm::vec2), &geom->tex_coords[0], GL_STATIC_DRAW);
			// Enable attribute pointer for texture coordinate data
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(2);
		}

		// If we have colour data, then add to the vertex array object
		if (geom->colours.size() > 0)
		{
			// Generate buffer
			glGenBuffers(1, &geom->colour_buffer);
			// Bind buffer
			glBindBuffer(GL_ARRAY_BUFFER, geom->colour_buffer);
			// Set data for buffer
			glBufferData(GL_ARRAY_BUFFER, geom->colours.size() * sizeof(glm::vec4), &geom->colours[0], GL_STATIC_DRAW);
			// Enable attribute pointer for colour data
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(3);
		}

		// If there is normal data, generate tangent data if it doesn't already exist
		if (geom->normals.size() > 0 && geom->tangents.size() == 0)
		{
			// Iterate through each normal and generate 
			for (int i = 0; i < geom->normals.size(); ++i)
			{
				// Tangent
				glm::vec3 tangent;
				// Determine if tangent value. Get orthogonal with forward and up
				// Orthogonal to forward vector
				glm::vec3 c1 = glm::cross(geom->normals[i], glm::vec3(0.0f, 0.0f, 1.0f));
				// Orthogonal to up vector
				glm::vec3 c2 = glm::cross(geom->normals[i], glm::vec3(0.0f, 1.0f, 0.0f));
			
				// Determine which vector has greater length.  This will be the tangent
				if (glm::length2(c1) > glm::length2(c2))
					tangent = c1;
				else
					tangent = c2;

				// Normalize tangent.  Needs to be 1 long
				tangent = glm::normalize(tangent);

				// Add generated tangent to the geometry
				geom->tangents.push_back(tangent);
			}
		}

		// If we have tangent data, then add to the vertex array object
		if (geom->tangents.size() > 0)
		{
			// Generate buffer
			glGenBuffers(1, &geom->tangent_buffer);
			// Bind buffer
			glBindBuffer(GL_ARRAY_BUFFER, geom->tangent_buffer);
			// Set data for buffer
			glBufferData(GL_ARRAY_BUFFER, geom->tangents.size() * sizeof(glm::vec3), &geom->tangents[0], GL_STATIC_DRAW);
			// Enable attribute pointer for tangent data
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(4);
		}

		// If there is tangent data, generate binormal data if not already done
		if (geom->tangents.size() > 0 && geom->binormals.size() == 0)
		{
			// Iterate through all the tangent data and create binormal
			for (int i = 0; i < geom->tangents.size(); ++i)
			{
				// Binormal is just the cross product of the normal and tangent
				// Binormal value
				glm::vec3 binormal = glm::cross(geom->normals[i], geom->tangents[i]);
				// Add to geometry structure
				geom->binormals.push_back(binormal);
			}
		}

		// If we have binormal data, then add to the vertex array object
		if (geom->binormals.size() > 0)
		{
			// Generate buffer
			glGenBuffers(1, &geom->binormal_buffer);
			// Bind buffer
			glBindBuffer(GL_ARRAY_BUFFER, geom->binormal_buffer);
			// Set data for the buffer
			glBufferData(GL_ARRAY_BUFFER, geom->binormals.size() * sizeof(glm::vec3), &geom->binormals[0], GL_STATIC_DRAW);
			// Enable attribute pointer for binormal data
			glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(5);
		}

		// If we have index data, then initialise
		if (geom->indices.size() > 0)
		{
			// Generate buffer
			glGenBuffers(1, &geom->index_buffer);
			// Bind buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geom->index_buffer);
			// Set buffer data
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, geom->indices.size() * sizeof(unsigned int), &geom->indices[0], GL_STATIC_DRAW);
		}

		// Return true
		return true;
	}

	// Data required for box geometry
	glm::vec3 box_positions[24] =
	{
		// Front
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),

		// Right side
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),

		// Back
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),

		// Left side
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),

		// Top
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f),

		// Bottom
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f)
	};

    // Normals for the box geometry
    glm::vec3 box_normals[6] =
    {
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f)
    };

	glm::vec2 box_texcoords[4] =
	{
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f)
	};

	// Creates a simple box geometry
	std::shared_ptr<geometry> geometry_builder::create_box(const glm::vec3& dimensions)
	{
		// Type of geometry used will be quads
		auto geom = std::make_shared<geometry>();
		geom->geometry_type = GL_QUADS;
		// Iterate through each position and add to geometry.
		for (int i = 0; i < 24; ++i)
		{
			// Add the position to the position data
			// We multiply this value by the dimensions
			geom->positions.push_back(box_positions[i] * dimensions);
			// The normal is one of the six defined.  Divide index by 4 to get the value
			geom->normals.push_back(box_normals[i / 4]);
			// Set the colour to be light grey
			geom->colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
		}
        // Texture coordinates done seperately, based on side
        // Front
        for (int i = 0; i < 4; ++i)
            geom->tex_coords.push_back(box_texcoords[i] * glm::vec2(dimensions));
        // Right
        for (int i = 0; i < 4; ++i)
            geom->tex_coords.push_back(box_texcoords[i] * glm::vec2(dimensions.z, dimensions.y));
        // Back
        for (int i = 0; i < 4; ++i)
            geom->tex_coords.push_back(box_texcoords[i] * glm::vec2(dimensions));
        // Left
        for (int i = 0; i < 4; ++i)
            geom->tex_coords.push_back(box_texcoords[i] * glm::vec2(dimensions.z, dimensions.y));
        // Top
        for (int i = 0; i < 4; ++i)
            geom->tex_coords.push_back(box_texcoords[i] * glm::vec2(dimensions.x, dimensions.z));
        // Bottom
        for (int i = 0; i < 4; ++i)
            geom->tex_coords.push_back(box_texcoords[i] * glm::vec2(dimensions.x, dimensions.z));

		// Initialise geometry
		if (!initialise_geometry(geom))
            return nullptr;

		return geom;
	}

	// Tetrahedron data
	glm::vec3 tetra_positions[12] =
	{
		// Side 1
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.0f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.5f),

		// Side 2
		glm::vec3(0.0f, -0.5f, -0.5f),
		glm::vec3(0.0f, 0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.5f),

		// Side 3
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.0f, 0.5f, 0.0f),
		glm::vec3(0.0f, -0.5f, -0.5f),

		// Bottom
		glm::vec3(0.0f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f)
	};

	// Texture coordinates for the tetrahedron geometry
	glm::vec2 tetra_texcoords[3] = 
	{
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(0.0f, 0.0f)
	};

	// Creates a tetrahedron geometry
	std::shared_ptr<geometry> geometry_builder::create_tetrahedron(const glm::vec3& dimensions)
	{
		auto geom = std::make_shared<geometry>();
		geom->geometry_type = GL_TRIANGLES;
		// Iterate through each position and add to geometry.
		for (int i = 0; i < 12; ++i)
		{
			// Add the position to the position data
			// We multiply this value by the dimensions
			geom->positions.push_back(tetra_positions[i] * dimensions);
			// Set the colour to be light grey
			geom->colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
		}
		// For the normals, we use the cross product (because of dimensional scaling)
		for (int i = 0; i < 12; i += 3)
		{
			auto v1 = geom->positions[i + 1] - geom->positions[i];
			auto v2 = geom->positions[i + 2] - geom->positions[i];
			auto norm = glm::normalize(glm::cross(v1, v2));
			for (int j = 0; j < 3; ++j)
				geom->normals.push_back(norm);
		}
        // Texture coordinates done seperately, based on side
        // Side 1
        for (int i = 0; i < 3; ++i)
            geom->tex_coords.push_back(tetra_texcoords[i] * glm::vec2(dimensions));
        // Side 2
        for (int i = 0; i < 3; ++i)
            geom->tex_coords.push_back(tetra_texcoords[i] * glm::vec2(dimensions.z, dimensions.y));
        // Side 3
        for (int i = 0; i < 3; ++i)
            geom->tex_coords.push_back(tetra_texcoords[i] * glm::vec2(dimensions.z, dimensions.y));
        // Bottom
        for (int i = 0; i < 3; ++i)
            geom->tex_coords.push_back(tetra_texcoords[i] * glm::vec2(dimensions.z, dimensions.x));
        
		// Initialise geometry
		if (!initialise_geometry(geom))
            return nullptr;

		return geom;
	}

	// Pyramid data
	glm::vec3 pyramid_positions[18] =
	{
		// Front
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.0f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		// Right
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f, 0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		// Back
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f, 0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		// Left
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.0f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		// Bottom 1
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		// Bottom 2
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f)
	};

	std::shared_ptr<geometry> geometry_builder::create_pyramid(const glm::vec3& dimensions)
	{
		auto geom = std::make_shared<geometry>();
		geom->geometry_type = GL_TRIANGLES;
		// Iterate through each position and add to geometry.
		for (int i = 0; i < 18; ++i)
		{
			// Add the position to the position data
			// We multiply this value by the dimensions
			geom->positions.push_back(pyramid_positions[i] * dimensions);
			// Set the colour to be light grey
			geom->colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
		}
		// For the normals, we use the cross product (because of dimensional scaling)
		for (int i = 0; i < 18; i += 3)
		{
			auto v1 = geom->positions[i + 1] - geom->positions[i];
			auto v2 = geom->positions[i + 2] - geom->positions[i];
			auto norm = glm::normalize(glm::cross(v1, v2));
			for (int j = 0; j < 3; ++j)
				geom->normals.push_back(norm);
		}
        // Texture coordinates done seperately, based on side
        // Front, right, back and left based on tetrahedron
		for (int i = 0; i < 3; ++i)
            geom->tex_coords.push_back(tetra_texcoords[i] * glm::vec2(dimensions));
        for (int i = 0; i < 3; ++i)
            geom->tex_coords.push_back(tetra_texcoords[i] * glm::vec2(dimensions.z, dimensions.y));
        for (int i = 0; i < 3; ++i)
            geom->tex_coords.push_back(tetra_texcoords[i] * glm::vec2(dimensions));
		for (int i = 0; i < 3; ++i)
			geom->tex_coords.push_back(tetra_texcoords[i] * glm::vec2(dimensions.z, dimensions.y));
		// Bottom based on box
		// Bottom
        for (int i = 0; i < 3; ++i)
            geom->tex_coords.push_back(box_texcoords[i] * glm::vec2(dimensions.x, dimensions.z));
        geom->tex_coords.push_back(box_texcoords[0] * glm::vec2(dimensions.x, dimensions.z));
		geom->tex_coords.push_back(box_texcoords[2] * glm::vec2(dimensions.x, dimensions.z));
		geom->tex_coords.push_back(box_texcoords[3] * glm::vec2(dimensions.x, dimensions.z));

		// Initialise geometry
		if (!initialise_geometry(geom))
            return nullptr;

		return geom;
	}

	std::shared_ptr<geometry> geometry_builder::create_disk(int slices, const glm::vec2& dimensions)
	{
		// Create geometry
		auto geom = std::make_shared<geometry>();
		geom->geometry_type = GL_TRIANGLE_FAN;
		// Values to work with
		// Push centre
		geom->positions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		// Push normal
		geom->normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		// Calculate texture centre
		glm::vec2 tex_coord(0.5f, 0.5f);
		// Push the tex_coord
		geom->tex_coords.push_back(tex_coord);
		// Push the colour
		geom->colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

		// Working position
		glm::vec3 pos(0.5f * dimensions.x, 0.0f, 0.0f);
		// Push working position, normal, relevant tex coord and colour
		geom->positions.push_back(pos);
		geom->normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		geom->tex_coords.push_back(glm::vec2(tex_coord.x + pos.x, tex_coord.y + pos.z));
		geom->colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

		// Calculate angle per slice
		auto delta_angle = (2.0 * glm::pi<double>()) / static_cast<double>(slices);
		// Loop round each slice
		for (int i = 1; i < slices + 1; ++i)
		{
			// Calculate next position
			pos = glm::vec3(cos(i * delta_angle) * dimensions.x / 2.0f, 0.0f, -sin(i * delta_angle) * dimensions.y / 2.0f);
			// Push position, notmal, relevant tex coord and colour
			geom->positions.push_back(pos);
			geom->normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			geom->tex_coords.push_back(glm::vec2(tex_coord.x + pos.x, tex_coord.y + pos.z));
			geom->colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
		}

		// Try and initialise the geometry
		if (!initialise_geometry(geom))
			return nullptr;

		// Return geometry
		return geom;
	}

	std::shared_ptr<geometry> geometry_builder::create_cylinder(int stacks, int slices, const glm::vec3& dimensions)
	{
		// Create geometry
		auto geom = std::make_shared<geometry>();
		geom->geometry_type = GL_TRIANGLES;
	
		// Create top - similar to disk but now using triangles
		glm::vec3 centre(0.0f, 0.5f * dimensions.y, 0.0f);
		auto vertex_prev = glm::vec3(0.5f, 0.5f, 0.0f) * dimensions;
		glm::vec3 vertex_current;
		glm::vec2 tex_coord(0.5f, 0.5f);
		// Angle per slice
		auto delta_angle = (2.0f * glm::pi<float>()) / static_cast<float>(slices);
		// Iterate for each slice
		for (int i = 1; i <= slices; ++i)
		{
			// Calculate unit length vertex
			vertex_current = glm::vec3(cos(i * delta_angle), 1.0f, -sin(i * delta_angle));
			// We want radius to be 1.0f, so divide by 2.0f
			vertex_current /= 2.0f;
			// Multiply by dimensions
			vertex_current *= dimensions;
			// Push back vertices
			geom->positions.push_back(centre);
			geom->positions.push_back(vertex_prev);
			geom->positions.push_back(vertex_current);
			// Push back normals and colours
			for (int j = 0; j < 3; ++j)
			{
				geom->normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
				geom->colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
			}
			// Push back tex_coords
			geom->tex_coords.push_back(tex_coord);
			geom->tex_coords.push_back(glm::vec2(tex_coord.x + vertex_prev.x, tex_coord.y + vertex_prev.z));
			geom->tex_coords.push_back(glm::vec2(tex_coord.x + vertex_current.x, tex_coord.y + vertex_current.z));
			// Set previous as current
			vertex_prev = vertex_current;
		}

		// Create bottom - same process as top
		centre = glm::vec3(0.0f, -0.5f * dimensions.y, 0.0f);
		vertex_prev = glm::vec3(0.5f, -0.5f, 0.0f) * dimensions;
		// Iterate for each slice
		for (int i = 1; i <= slices; ++i)
		{
			// Calculate unit length vertex
			vertex_current = glm::vec3(cos(i * delta_angle), -1.0f, sin(i * delta_angle));
			// We want radius to be 1.0f, so divide by 2.0f
			vertex_current /= 2.0f;
			// Multiply by dimensions
			vertex_current *= dimensions;
			// Push back vertices
			geom->positions.push_back(centre);
			geom->positions.push_back(vertex_prev);
			geom->positions.push_back(vertex_current);
			// Push back normals and colours
			for (int j = 0; j < 3; ++j)
			{
				geom->normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				geom->colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
			}
			// Push back tex_coords
			geom->tex_coords.push_back(tex_coord);
			geom->tex_coords.push_back(glm::vec2(tex_coord.x + vertex_prev.x, tex_coord.y + vertex_prev.z));
			geom->tex_coords.push_back(glm::vec2(tex_coord.x + vertex_current.x, tex_coord.y + vertex_current.z));
			// Set previous as current
			vertex_prev = vertex_current;
		}

		// Create stacks
		auto vertices = std::array<glm::vec3, 4>();
		auto tex_coords = std::array<glm::vec2, 4>();
		// We will scale delta_height during vertex creation.  Use unit length here
		auto delta_height = 2.0f / static_cast<float>(stacks);
		// Calculate circumferance of the cylinder - could now be ellipitical
		auto circ = glm::pi<float>() * ((3 * (dimensions.x + dimensions.z)) - (sqrt((3.0f * dimensions.x + dimensions.z) * (dimensions.x + 3 * dimensions.z))));
		// Delta width is the circumference divided into slices
		auto delta_width = circ / static_cast<float>(slices);
		for (int i = 0; i < stacks; ++i)
		{
			for (int j = 0; j < slices; ++j)
			{
				// Calculate vertices
				vertices[0] = glm::vec3(cos(j * delta_angle), 1.0f - (delta_height * i), sin(j * delta_angle));
				vertices[1] = glm::vec3(cos((j + 1) * delta_angle), 1.0f - (delta_height * i), sin((j + 1) * delta_angle));
				vertices[2] = glm::vec3(cos(j * delta_angle), 1.0f - (delta_height * (i + 1)), sin(j * delta_angle));
				vertices[3] = glm::vec3(cos((j + 1) * delta_angle), 1.0f - (delta_height * (i + 1)), sin((j + 1) * delta_angle));
				// Scale by 0.5 * dimensions
				for (auto& v : vertices)
					v *= dimensions * 0.5f;

				// Calculate tex_coords
				tex_coords[0] = glm::vec2(delta_width * j, (dimensions.y * 0.5f) - ((delta_height * i * dimensions.y) / 2.0f));
				tex_coords[1] = glm::vec2(delta_width * (j + 1), (dimensions.y * 0.5f) - ((delta_height * i * dimensions.y) / 2.0f));
				tex_coords[2] = glm::vec2(delta_width * j, (dimensions.y * 0.5f) - ((delta_height * (i + 1) * dimensions.y) / 2.0f));
				tex_coords[3] = glm::vec2(delta_width * (j + 1), (dimensions.y * 0.5f) - ((delta_height * (i + 1) * dimensions.y) / 2.0f));

				// Triangle 1
				geom->positions.push_back(vertices[0]);
				geom->normals.push_back(glm::normalize(glm::vec3(vertices[0].x, 0.0f, vertices[0].z)));
				geom->tex_coords.push_back(tex_coords[0]);
				geom->positions.push_back(vertices[3]);
				geom->normals.push_back(glm::normalize(glm::vec3(vertices[3].x, 0.0f, vertices[3].z)));
				geom->tex_coords.push_back(tex_coords[3]);
				geom->positions.push_back(vertices[2]);
				geom->normals.push_back(glm::normalize(glm::vec3(vertices[2].x, 0.0f, vertices[2].z)));
				geom->tex_coords.push_back(tex_coords[2]);
				// Triangle 2
				geom->positions.push_back(vertices[0]);
				geom->normals.push_back(glm::normalize(glm::vec3(vertices[0].x, 0.0f, vertices[0].z)));
				geom->tex_coords.push_back(tex_coords[0]);
				geom->positions.push_back(vertices[1]);
				geom->normals.push_back(glm::normalize(glm::vec3(vertices[1].x, 0.0f, vertices[1].z)));
				geom->tex_coords.push_back(tex_coords[1]);
				geom->positions.push_back(vertices[3]);
				geom->normals.push_back(glm::normalize(glm::vec3(vertices[3].x, 0.0f, vertices[3].z)));
				geom->tex_coords.push_back(tex_coords[3]);

				// Colours
				for (int k = 0; k < 6; ++k)
					geom->colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
			}
		}

		// Try and initialise the geometry
		if (!initialise_geometry(geom))
			return nullptr;

		// Return geometry
		return geom;
	}

	std::shared_ptr<geometry> geometry_builder::create_sphere(int stacks, int slices, const glm::vec3& dimensions)
	{
        auto geom = std::make_shared<geometry>();
        // Create required values
        float deltaRho = glm::pi<float>() / stacks;
        float deltaTheta = 2.0f * glm::pi<float>() / slices;
        float deltaT = dimensions.y / (float)stacks;
        float deltaS = dimensions.x / (float)slices;
        float t = dimensions.y;
        float s = 0.0f;

        for (int i = 0; i < stacks; ++i)
        {
            float rho = i * deltaRho;
            s = 0.0f;
            glm::vec3 vertices[4];
            glm::vec2 texcoords[4];
            for (int j = 0; j < slices; ++j)
            {
                // Vertex 0
                float theta = j * deltaTheta;
                vertices[0] = glm::vec3(dimensions.x * -sin(theta) * sin(rho), 
                                        dimensions.y * cos(theta) * sin(rho), 
                                        dimensions.z * cos(rho));
                texcoords[0] = glm::vec2(s, t);
                // Vertex 1
                vertices[1] = glm::vec3(dimensions.x * -sin(theta) * sin(rho + deltaRho), 
                                        dimensions.y * cos(theta) * sin(rho + deltaRho), 
                                        dimensions.z * cos(rho + deltaRho));
                texcoords[1] = glm::vec2(s, t - deltaT);
                // Vertex 2
                theta = ((j + 1) == slices) ? 0.0f : (j + 1) * deltaTheta;
                s += deltaS;
                vertices[2] = glm::vec3(dimensions.x * -sin(theta) * sin(rho), 
                                        dimensions.y * cos(theta) * sin(rho), 
                                        dimensions.z * cos(rho));
                texcoords[2] = glm::vec2(s, t);
                // Vertex 3
                vertices[3] = glm::vec3(dimensions.x * -sin(theta) * sin(rho + deltaRho), 
                                        dimensions.y * cos(theta) * sin(rho + deltaRho), 
                                        dimensions.z * cos(rho + deltaRho));
                texcoords[3] = glm::vec2(s, t - deltaT);

                // Triangle 1
                geom->positions.push_back(vertices[0]);
                geom->normals.push_back(glm::normalize(glm::vec3(vertices[0])));
                geom->tex_coords.push_back(texcoords[0]);
                geom->positions.push_back(vertices[1]);
                geom->normals.push_back(glm::normalize(glm::vec3(vertices[1])));
                geom->tex_coords.push_back(texcoords[1]);
                geom->positions.push_back(vertices[2]);
                geom->normals.push_back(glm::normalize(glm::vec3(vertices[2])));
                geom->tex_coords.push_back(texcoords[2]);

                // Triangle 2
                geom->positions.push_back(vertices[1]);
                geom->normals.push_back(glm::normalize(glm::vec3(vertices[1])));
                geom->tex_coords.push_back(texcoords[1]);
                geom->positions.push_back(vertices[3]);
                geom->normals.push_back(glm::normalize(glm::vec3(vertices[3])));
                geom->tex_coords.push_back(texcoords[3]);
                geom->positions.push_back(vertices[2]);
                geom->normals.push_back(glm::normalize(glm::vec3(vertices[2])));
                geom->tex_coords.push_back(texcoords[2]);
            }

            t -= deltaT;
        }

        // Initialise geometry
        if (!initialise_geometry(geom))
            return nullptr;

		return geom;
	}

	// Helper function to divide a triangle for subdivision purposes
	void divide_triangle(std::shared_ptr<geometry> geom, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, int divisions, const glm::vec3& dimensions)
	{
		// Do we have more divisions to do?
		if (divisions > 0)
		{
			// Calculate new vertices to work on
			std::array<glm::vec3, 3> v;
			v[0] = glm::normalize(a + b) * dimensions;
			v[1] = glm::normalize(a + c) * dimensions;
			v[2] = glm::normalize(b + c) * dimensions;
			// Divide new triangles
			divide_triangle(geom, a, v[0], v[1], divisions - 1, dimensions);
			divide_triangle(geom, c, v[1], v[2], divisions - 1, dimensions);
			divide_triangle(geom, b, v[2], v[0], divisions - 1, dimensions);
			divide_triangle(geom, v[0], v[2], v[1], divisions - 1, dimensions);
		}
		else
		{
			// Otherwise add a triangle to the geometry
			geom->positions.push_back(a);
			geom->normals.push_back(glm::normalize(a));
			geom->positions.push_back(b);
			geom->normals.push_back(glm::normalize(b));
			geom->positions.push_back(c);
			geom->normals.push_back(glm::normalize(c));
			for (int i = 0; i < 3; ++i)
				geom->colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
		}
	}

	std::shared_ptr<geometry> geometry_builder::create_sphere_subdivision(int subdivisions, const glm::vec3& dimensions)
	{
		// Create geometry
		auto geom = std::make_shared<geometry>();
		geom->geometry_type = GL_TRIANGLES;

		// Create starting geometry
		std::array<glm::vec3, 4> v =
		{
			glm::vec3(0.0f, 0.0f, 1.0f) * dimensions * 0.5f,
			glm::vec3(0.0f, 0.942809f, -0.333333f) * dimensions * 0.5f,
			glm::vec3(-0.816497f, -0.471405f, -0.333333f) * dimensions * 0.5f,
			glm::vec3(0.816497f, -0.471405f, -0.333333f) * dimensions * 0.5f
		};

		// Divide the triangles
		divide_triangle(geom, v[0], v[1], v[2], subdivisions, dimensions * 0.5f);
		divide_triangle(geom, v[3], v[2], v[1], subdivisions, dimensions * 0.5f);
		divide_triangle(geom, v[0], v[3], v[1], subdivisions, dimensions * 0.5f);
		divide_triangle(geom, v[0], v[2], v[3], subdivisions, dimensions * 0.5f);

		// Initialise geometry
		if (!initialise_geometry(geom))
			return nullptr;

		// Return geometry
		return geom;
	}

	std::shared_ptr<geometry> geometry_builder::create_torus(int stacks, int slices, float ring_radius, float outer_radius)
	{
		// Create geometry
		auto geom = std::make_shared<geometry>();
		geom->geometry_type = GL_TRIANGLES;

		// Calculate delta for stack and slice
		auto delta_stack = 2.0f * glm::pi<float>() / static_cast<float>(stacks);
		auto delta_slice = 2.0f * glm::pi<float>() / static_cast<float>(slices);

		// Calculate outer circumference and ring circumference
		auto outer_circ = 2.0f * glm::pi<float>() * outer_radius;
		auto ring_circ = 2.0f * glm::pi<float>() * ring_radius;

		// Create stacks for torus
		for (int i = 0; i < stacks; ++i)
		{
			auto a0 = i * delta_stack;
			auto a1 = a0 + delta_stack;
			std::array<glm::vec3, 4> vertices;
			std::array<glm::vec3, 4> normals;
			std::array<glm::vec2, 4> tex_coords;

			// Iterate through each slice for stack
			for (int j = 0; j <= slices; ++j)
			{
				auto b = j * delta_slice;
				auto c = cos(j * delta_slice) * ring_radius;
				auto r = c + outer_radius;

				// Calculate values
				vertices[0] = glm::vec3(sin(a0) * r, sin(j * delta_slice) * ring_radius, cos(a0) * r);
				normals[0] = glm::vec3(sin(a0) * c, cos(a0) * c, sin(b));
				tex_coords[0] = glm::vec2((static_cast<float>(i) / static_cast<float>(stacks)) * outer_circ, (static_cast<float>(j) / static_cast<float>(slices)) * ring_circ);
				vertices[1] = glm::vec3(sin(a1) * r, sin(j * delta_slice) * ring_radius, cos(a1) * r);
				normals[1] = glm::vec3(sin(a1) * c, cos(a1) * c, sin(b));
				tex_coords[1] = glm::vec2((static_cast<float>(i + 1) / static_cast<float>(stacks)) * outer_circ, (static_cast<float>(j) / static_cast<float>(slices)) * ring_circ);
				// Update working values
				c = cos((j + 1) * delta_slice) * ring_radius;
				r = c + outer_radius;
				vertices[2] = glm::vec3(sin(a0) * r, sin((j + 1) * delta_slice) * ring_radius, cos(a0) * r);
				normals[2] = glm::vec3(sin(a0) * c, cos(a0) * c, sin(b));
				tex_coords[2] = glm::vec2((static_cast<float>(i) / static_cast<float>(stacks)) * outer_circ, (static_cast<float>(j + 1) / static_cast<float>(slices)) * ring_circ);
				vertices[3] = glm::vec3(sin(a1) * r, sin((j + 1) * delta_slice) * ring_radius, cos(a1) * r);
				normals[3] = glm::vec3(sin(a1) * c, cos(a1) * c, sin(b));
				tex_coords[3] = glm::vec2((static_cast<float>(i + 1) / static_cast<float>(stacks)) * outer_circ, (static_cast<float>(j + 1) / static_cast<float>(slices)) * ring_circ);

				// Triangle 1
				geom->positions.push_back(vertices[0]);
				geom->positions.push_back(vertices[1]);
				geom->positions.push_back(vertices[2]);
				geom->normals.push_back(glm::normalize(normals[0]));
				geom->normals.push_back(glm::normalize(normals[1]));
				geom->normals.push_back(glm::normalize(normals[2]));
				geom->tex_coords.push_back(tex_coords[0]);
				geom->tex_coords.push_back(tex_coords[1]);
				geom->tex_coords.push_back(tex_coords[2]);

				// Triangle 2
				geom->positions.push_back(vertices[1]);
				geom->positions.push_back(vertices[3]);
				geom->positions.push_back(vertices[2]);
				geom->normals.push_back(glm::normalize(normals[1]));
				geom->normals.push_back(glm::normalize(normals[3]));
				geom->normals.push_back(glm::normalize(normals[2]));
				geom->tex_coords.push_back(tex_coords[1]);
				geom->tex_coords.push_back(tex_coords[3]);
				geom->tex_coords.push_back(tex_coords[2]);

				// Push colours
				for (int k = 0; k < 6; ++k)
					geom->colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
			}
		}

		// Initialise geometry
		if (!initialise_geometry(geom))
			return nullptr;

		// Return geometry
		return geom;
	}

	std::shared_ptr<geometry> geometry_builder::create_plane(int width, int depth)
	{
		// Type of geometry used will be triangles
		auto geom = std::make_shared<geometry>();
		geom->geometry_type = GL_TRIANGLES;
		// Iterate through each vertex and add to geometry.
        glm::vec3 vertices[4];
        for (int x = 0; x < width; ++x)
        {
            for (int z = 0; z < depth; ++z)
            {
                vertices[0] = glm::vec3(-float(width) / 2.0f + x, 0.0f, float(depth) / 2.0f - z);
                vertices[1] = glm::vec3(-float(width) / 2.0f + (x + 1), 0.0f, float(depth) / 2.0f - z);
                vertices[2] = glm::vec3(-float(width) / 2.0f + x, 0.0f, float(depth) / 2.0f - (z + 1));
                vertices[3] = glm::vec3(-float(width) / 2.0f + (x + 1), 0.0f, float(depth) / 2.0f - (z + 1));
            
                // Triangle 1
                geom->positions.push_back(vertices[0]);
                geom->tex_coords.push_back(glm::vec2(x , z) / 10.0f);
                geom->positions.push_back(vertices[3]);
                geom->tex_coords.push_back(glm::vec2(x + 1, z + 1) / 10.0f);
                geom->positions.push_back(vertices[2]);
                geom->tex_coords.push_back(glm::vec2(x, z + 1) / 10.0f);
                // Triangle 2
                geom->positions.push_back(vertices[0]);
                geom->tex_coords.push_back(glm::vec2(x, z) / 10.0f);
                geom->positions.push_back(vertices[1]);
                geom->tex_coords.push_back(glm::vec2(x + 1, z) / 10.0f);
                geom->positions.push_back(vertices[3]);
                geom->tex_coords.push_back(glm::vec2(x + 1, z + 1) / 10.0f);

                // Add normals.  All are up.  Also add colours
                for (int i = 0; i < 6; ++i)
                {
                    geom->normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                    geom->colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
                }
            }
        }

		// Initialise geometry
		if (!initialise_geometry(geom))
			return nullptr;

		return geom;
	}

	void divide_sierpinski(std::shared_ptr<geometry> geom, const std::array<glm::vec3, 4> vertices, int count)
	{
		// Check if we have completed the subdivisions
		if (count > 0)
		{
			// Calculate new vertices
			std::array<glm::vec3, 6> v;
			v[0] = vertices[0] + ((vertices[1] - vertices[0]) / 2.0f);
			v[1] = vertices[0] + ((vertices[2] - vertices[0]) / 2.0f);
			v[2] = vertices[0] + ((vertices[3] - vertices[0]) / 2.0f);
			v[3] = vertices[1] + ((vertices[2] - vertices[1]) / 2.0f);
			v[4] = vertices[1] + ((vertices[3] - vertices[1]) / 2.0f);
			v[5] = vertices[2] + ((vertices[3] - vertices[2]) / 2.0f);
			
			// Temp working vertices
			std::array<glm::vec3, 4> temp_verts;

			// Tetrahedron 1
			temp_verts[0] = vertices[0];
			temp_verts[1] = v[0];
			temp_verts[2] = v[1];
			temp_verts[3] = v[2];
			divide_sierpinski(geom, temp_verts, count - 1);

			// Tetrahedron 2
			temp_verts[0] = v[0];
			temp_verts[1] = vertices[1];
			temp_verts[2] = v[3];
			temp_verts[3] = v[4];
			divide_sierpinski(geom, temp_verts, count - 1);

			// Tetrahedron 3
			temp_verts[0] = v[1];
			temp_verts[1] = vertices[2];
			temp_verts[2] = v[3];
			temp_verts[3] = v[5];
			divide_sierpinski(geom, temp_verts, count - 1);

			// Tetrahedron 4
			temp_verts[0] = v[2];
			temp_verts[1] = vertices[3];
			temp_verts[2] = v[4];
			temp_verts[3] = v[5];
			divide_sierpinski(geom, temp_verts, count - 1);
		}
		else
		{
			// Last in a division.  Create triangles
			for (int i = 0; i < 12; ++i)
			{
				
			}
		}
	}

	std::shared_ptr<geometry> geometry_builder::create_sierpinski(int subdivisions)
	{
		// Create geometry
		auto geom = std::make_shared<geometry>();
		geom->geometry_type = GL_TRIANGLES;

		// 

		// Initialise geometry
		if (!initialise_geometry(geom))
			return nullptr;

		return geom;
	}
}