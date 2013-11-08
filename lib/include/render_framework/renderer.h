#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <GL\glew.h>
#include <GL\glfw3.h>
#include <glm\glm.hpp>

namespace render_framework
{
	// Forward declaration of camera
	class camera;

	// Forward declaration of geometry types
	struct geometry;
	struct model;

	// Forward declaration of texture types
	struct texture;
	struct cube_map;
	struct skybox;

	// Forward declaration of terrain
	struct terrain;

	// Forward declaration of material
	struct material;

	// Forward declaration of mesh
	struct mesh;

	// Forward declaration of lighting
	struct directional_light;
	struct point_light;
	struct spot_light;
	struct dynamic_lights;

	// Forward declaration of effect
	struct effect;

	// Forward declaration for buffers
	struct frame_buffer;
	struct depth_buffer;
	struct shadow_map;

	// Forward declaration for post processing
	struct render_pass;
	struct post_process;

	/*
	This class is responsible for rendering objects to the screen, by allowing
	the binding of values such as effects and buffers, and also the rendering of
	objects such as geometry, sky boxes, terrain, etc.  This class is at the
	heart of the render framework.
	*/
	class renderer
	{
	private:
		// Window being used by the renderer
		GLFWwindow* _window;
		// Window caption
		std::string _caption;
		// Flag indicating that the renderer is still running
		bool _running;
		// The width of the window being used by the render framework
		unsigned int _width;
		// The height of the window being used by the render framework
		unsigned int _height;
		// Currently bound effect
		std::shared_ptr<effect> _effect;
		// Currently bound camera
		std::shared_ptr<camera> _camera;
		// Current view matrix used by the render framework
		glm::mat4 _view;
		// Current projection matrix used by the render framework
		glm::mat4 _projection;
		// Current shadow map being used - if relevant
		std::shared_ptr<shadow_map> _shadow_map;
		// Private constructor.  Class is a singleton
		renderer() : _caption("Render Framework") { }
		// Private copy constructor
		renderer(const renderer&) { }
		// Private assignment operator
		void operator=(renderer&) { }
	public:
		// Destructor for renderer.
		~renderer() { shutdown(); }
		// Gets the singleton instance
		static renderer& get_instance()
		{
			// Creates static instance of the renderer
			static renderer instance;
			// Return static instance
			return instance;
		}

		// Gets the window used by the renderer
		GLFWwindow* get_window() { return _window; }

		// Sets the window caption
		void set_caption(const std::string& caption) { _caption = caption; }

		// Gets the current running state of the renderer
		bool is_running() const { return _running; }

		// Sets the running state of the renderer
		void set_running(bool value) { _running = value; }

		// Gets the width of the render window in pixels
		unsigned int get_screen_width() const { return _width; }

		// Gets the height of the render window in pixels
		unsigned int get_screen_height() const { return _height; }

		// Gets the currently used camera for the renderer
		std::shared_ptr<camera> get_camera() { return _camera; }

		// Sets the currently used camera for the renderer
		void set_camera(std::shared_ptr<camera> value) { _camera = value; }

		// Gets the current view matrix used by the renderer
		glm::mat4 get_view() const { return _view; }

		// Sets the current view matrix used by the renderer.
		void set_view(const glm::mat4& value) { _view = value; }

		// Gets the current projection matrix used by the renderer
		glm::mat4 get_projection() const { return _projection; }

		// Sets the current projection matrix used by the renderer
		void set_projection(const glm::mat4& value) { _projection = value; }

		// Initialises the render framework
		bool initialise();

		// Shuts down the render framework
		void shutdown();

		// Begins a render
		bool begin_render();

		// Ends a render
		bool end_render();

		// Begins a shadow render
		bool begin_shadow_render();

		// Ends a shadow render
		bool end_shadow_render();

		// Clears the screen and associated buffers
		void clear();

		// Swaps the front and back buffers
		void swap_buffers();

		// Binds a value with the renderer.
		template <typename T>
		bool bind(std::shared_ptr<T> value);

		// Binds a texture with the renderer
		template <typename T>
		bool bind_texture(std::shared_ptr<T> value, unsigned int index);

		// Sets a uniform on the currently bound effect
		template <typename T>
		bool set_uniform(const std::string& name, const T& value);

		// Sets a uniform block on the currently bound effect
		bool set_uniform_block(const std::string& name, unsigned int buffer, int size);

		// Renders an object to the screen
		template <typename T>
		bool render(std::shared_ptr<T> value);

		// Renders an object to the shadow texture
		template <typename T>
		bool shadow_render(std::shared_ptr<T> value);
	};

	/*
	Default bind operation.  Called when an attempt is made to bind a value of
	an unknown / incorrect type.  Will display an error and return false.
	*/
	template <typename T>
	bool renderer::bind(std::shared_ptr<T> value)
	{
		// Display error.  Incorrect type used
		std::cerr << "Error binding value of unknown type" << std::endl;
		std::cerr << "Type: " << typeid(T).name() << std::endl;
		// Return false
		return false;
	}

	/*
	Binds an effect with the renderer.  This effect will be used until another
	effect is bound in its place
	*/
	extern template
		bool renderer::bind(std::shared_ptr<effect> value);

	/*
	Binds a frame buffer with the renderer.  The frame buffer will be used until
	another frame buffer is bound in its place
	*/
	extern template
		bool renderer::bind(std::shared_ptr<frame_buffer> value);

	/*
	Binds a depth buffer with the renderer.  The depth buffer will be used until
	another frame buffer is bound in its place
	*/
	extern template
		bool renderer::bind(std::shared_ptr<depth_buffer> value);

	/*
	Binds a shadow map with the renderer.  The shadow map will be used until
	another frame buffer is bound in its place.
	*/
	extern template
		bool renderer::bind(std::shared_ptr<shadow_map> value);

	/*
	Binds a render pass with the renderer.  The render pass will be used until
	another render pass / frame buffer is bound in its place
	*/
	extern template
		bool renderer::bind(std::shared_ptr<render_pass> value);

	/*
	Binds a post_process with the renderer.  The post process will be used until
	another post process is bound in its place
	*/
	extern template
		bool renderer::bind(std::shared_ptr<post_process> value);

	/*
	Default method called when a bind texture call is made.  This is called when
	the value attempted to be bound is of an unknown / incorrect type.  Will
	display an error and return false.
	*/
	template <typename T>
	bool renderer::bind_texture(std::shared_ptr<T> value, unsigned int index)
	{
		std::cerr << "Attempted to bind texture of unknown type" << std::endl;
		std::cerr << "Type: " << typeid(T).name() << std::endl;
		return false;
	}

	/*
	Binds a texture at the given index.  Index is then used in a uniform binding
	*/
	extern template
		bool renderer::bind_texture(std::shared_ptr<texture> value, unsigned int index);

	/*
	Binds a cube map at the given index.  Index is then used in a uniform binding
	*/
	extern template
		bool renderer::bind_texture(std::shared_ptr<cube_map> value, unsigned int index);

	/*
	Default method called when a set uniform call is made.  This is called when
	an attempt to set a uniform of an unknown type is made.  Will display an
	error and return false.
	*/
	template <typename T>
	bool renderer::set_uniform(const std::string& name, const T& value)
	{
		// Display error messsage
		std::cerr << "Error trying to set uniform of unknown type" << std::endl;
		std::cerr << "Type: " << typeid(T).name() << std::endl;
		// Return false
		return false;
	}

	/*
	Sets the given uniform name with the int value provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const int& value);

	/*
	Sets the given uniform name with the double value provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const double& value);

	/*
	Sets the given uniform name with the float value provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const float& value);

	/*
	Sets the given uniform name with the unsigned int value provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const unsigned int& value);

	/*
	Sets the given uniform name with the vec2 value provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const glm::vec2& value);

	/*
	Sets the given uniform name with the vec3 value provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const glm::vec3& value);

	/*
	Sets the given uniform name with the vec4 value provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const glm::vec4& value);

	/*
	Sets the given uniform name with the mat2 value provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const glm::mat2& value);

	/*
	Sets the given uniform name with the mat3 value provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const glm::mat3& value);

	/*
	Sets the given uniform name with the mat4 value provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const glm::mat4& value);

	/*
	Sets the given uniform name with the material provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const material& value);

	/*
	Sets the given uniform name with the directional light value provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const directional_light& value);

	/*
	Sets the given uniform name with the point light value provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const point_light& value);

	/*
	Sets the given uniform name with the spot light value provided
	*/
	extern template
		bool renderer::set_uniform(const std::string& name, const spot_light& value);

	/*
	Default method called when a render call is made.  This method is called when
	the type of object is unknown / incorrect.  This method will display an error
	and return false.
	*/
	template <typename T>
	bool renderer::render(std::shared_ptr<T> value)
	{
		// Display error message
		std::cerr << "Error trying to render object of unknown type" << std::endl;
		std::cerr << "Type: " << typeid(T).name() << std::endl;
		// Return false
		return false;
	}

	/*
	Renders a piece of geometry to the scene
	*/
	extern template
		bool renderer::render(std::shared_ptr<geometry> value);

	/*
	Renders a model to the scene
	*/
	extern template
		bool renderer::render(std::shared_ptr<model> value);

	/*
	Renders a texture to the screen.  Assumes that the texture should take up
	the whole screen
	*/
	extern template
		bool renderer::render(std::shared_ptr<texture> value);

	/*
	Renders a skybox to the scene
	*/
	extern template
		bool renderer::render(std::shared_ptr<skybox> value);

	/*
	Renders a piece of terrain to the scene
	*/
	extern template
		bool renderer::render(std::shared_ptr<terrain> value);

	/*
	Renders a mesh to the scene
	*/
	extern template
		bool renderer::render(std::shared_ptr<mesh> value);

	/*
	Renders a frame buffer to the screen.  Assumes that the frame buffer should
	take up the entire screen.
	*/
	extern template
		bool renderer::render(std::shared_ptr<frame_buffer> value);

	/*
	Renders a depth buffer to the screen.  Assumes that the depth buffer should
	take up the entire screen
	*/
	extern template
		bool renderer::render(std::shared_ptr<depth_buffer> value);

	/*
	Renders a shadow map to the screen.  Assumes that the shadow map should take
	up the entire screen
	*/
	extern template
		bool renderer::render(std::shared_ptr<shadow_map> value);

	/*
	Renders a render pass to the screen.  Assumes that the render pass should
	take up the entire screen
	*/
	extern template
		bool renderer::render(std::shared_ptr<render_pass> value);

	/*
	Renders a post process to the screen.  Assumes that the post process should
	take up the entire screen
	*/
	extern template
		bool renderer::render(std::shared_ptr<post_process> value);

	/*
	Default method called when a shadow render call is made.  This method is called when
	the type of object is unknown / incorrect.  This method will display an error
	and return false.
	*/
	template <typename T>
	bool renderer::shadow_render(std::shared_ptr<T> value)
	{
		// Display error message
		std::cerr << "Error trying to render the shadow of an object of unknown type" << std::endl;
		std::cerr << "Type: " << typeid(T).name() << std::endl;
		// Return false
		return false;
	}

	/*
	Renders the shadow of a piece of geometry to the scene
	*/
	extern template
		bool renderer::shadow_render(std::shared_ptr<geometry> value);

	/*
	Renders the shadow of a model to the scene
	*/
	extern template
		bool renderer::shadow_render(std::shared_ptr<model> value);

	/*
	Renders the shadow of a piece of terrain to the scene
	*/
	extern template
		bool renderer::shadow_render(std::shared_ptr<terrain> value);

	/*
	Renders the shadow of a mesh to the scene
	*/
	extern template
		bool renderer::shadow_render(std::shared_ptr<mesh> value);
}