#pragma once

#include <vector>
#include <memory>
#include <GL\glew.h>
#include <glm\glm.hpp>

namespace render_framework
{
	/*
	A structure that stores information representing a geometric object
	*/
	struct geometry
	{
		// Type of geometry to use
		GLenum geometry_type;
		// Vertex array ID as stored by OpenGL
		GLuint vertex_array_object;
		// ID of buffer of position data as stored by OpenGL
		GLuint position_buffer;
		// ID of buffer of normal data as stored by OpenGL
		GLuint normal_buffer;
		// ID of buffer of texture coordinate data as stored by OpenGL
		GLuint tex_coord_buffer;
		// ID of buffer of tangent data as stored by OpenGL
		GLuint tangent_buffer;
		// ID of buffer of binormal data as stored by OpenGL
		GLuint binormal_buffer;
		// ID of buffer of colour data as stored by OpenGL
		GLuint colour_buffer;
		// ID of buffer of indices as stored by OpenGL
		GLuint index_buffer;

		// Vector containing position data
		std::vector<glm::vec3> positions;
		// Vector containing normal data
		std::vector<glm::vec3> normals;
		// Vector containing texture coordinate data
		std::vector<glm::vec2> tex_coords;
		// Vector containing tangent data
		std::vector<glm::vec3> tangents;
		// Vector containing binormal data
		std::vector<glm::vec3> binormals;
		// Vector containing colour data
		std::vector<glm::vec4> colours;
		// Vector containing index data
		std::vector<unsigned int> indices;

		/*
		Creates a new piece of geometry.  Ensures all buffers are set to 0
		(no buffer)
		*/
		geometry() : geometry_type(GL_TRIANGLES),
					 vertex_array_object(0),
					 position_buffer(0),
					 normal_buffer(0),
					 tex_coord_buffer(0),
					 tangent_buffer(0),
					 binormal_buffer(0),
					 colour_buffer(0),
					 index_buffer(0)
		{
		}

		/*
		Destroys a piece of geometry.  Will delete all buffers if they are valid
		*/
		~geometry()
		{
			// For each buffer, check if valid (non 0) and delete buffer accordingly
			if (position_buffer) glDeleteBuffers(1, &position_buffer);
			if (normal_buffer) glDeleteBuffers(1, &normal_buffer);
			if (tex_coord_buffer) glDeleteBuffers(1, &tex_coord_buffer);
			if (tangent_buffer) glDeleteBuffers(1, &tangent_buffer);
			if (binormal_buffer) glDeleteBuffers(1, &binormal_buffer);
			if (colour_buffer) glDeleteBuffers(1, &colour_buffer);
			if (index_buffer) glDeleteBuffers(1, &index_buffer);
			if (vertex_array_object) glDeleteVertexArrays(1, &vertex_array_object);
			// Set all buffer values to 0 (no buffer)
			vertex_array_object = position_buffer = normal_buffer = tex_coord_buffer
			= tangent_buffer = binormal_buffer = colour_buffer = index_buffer = 0;
		}
	};

	/*
	A helper class that allows the building of simple geometric objects
	*/
	class geometry_builder
	{
	public:
		// Initialises a piece of geometry
		static bool initialise_geometry(std::shared_ptr<geometry> geom);
		// Creates a simple box geometry
		static std::shared_ptr<geometry> create_box(const glm::vec3& dimensions = glm::vec3(1.0f, 1.0f, 1.0f));
		// Creates a tetrahedron geometry
		static std::shared_ptr<geometry> create_tetrahedron(const glm::vec3& dimensions = glm::vec3(1.0f, 1.0f, 1.0f));
		// Creates a pyramid piece of geometry
		static std::shared_ptr<geometry> create_pyramid(const glm::vec3& dimensions = glm::vec3(1.0f, 1.0f, 1.0f));
		// Creates a disk piece of geometry
		static std::shared_ptr<geometry> create_disk(int slices = 10, const glm::vec2& dimensions = glm::vec2(1.0f, 1.0f));
		// Creates a cylinder piece of geometry
		static std::shared_ptr<geometry> create_cylinder(int stacks = 10, int slices = 10, const glm::vec3& dimensions = glm::vec3(1.0f, 1.0f, 1.0f));
		// Creates a sphere piece of geometry
		static std::shared_ptr<geometry> create_sphere(int stacks = 10, int slices = 10, const glm::vec3& dimensions = glm::vec3(1.0f, 1.0f, 1.0f));
		// Creates a sphere piece of geometry by a subdivision method
		static std::shared_ptr<geometry> create_sphere_subdivision(int subdivisions = 10, const glm::vec3& dimensions = glm::vec3(1.0f, 1.0f, 1.0f));
		// Creates a torus piece of geometry
		static std::shared_ptr<geometry> create_torus(int stacks = 10, int slices = 10, float ring_radius = 1.0f, float outer_radius = 3.0f);
		// Creates a plane piece of geometry
		static std::shared_ptr<geometry> create_plane(int width = 100, int depth = 100);
		// Creates a sierpinski gasket
		static std::shared_ptr<geometry> create_sierpinski(int subdivisions = 3);
	};
}