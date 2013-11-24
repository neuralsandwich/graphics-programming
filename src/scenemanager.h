#include <render_framework\render_framework.h>

using namespace std;
using namespace render_framework;

class SceneManager {
public:
	// Destructor for SceneManager
	~SceneManager() { shutdown(); };

	// Gets singleton instance o
	static SceneManager& get_instance()
	{
		static SceneManager instance;

		return instance;
	}

	// Gets the current running state of the renderer
	bool is_running() const { return _running; }

	// Initialise the SceneManager
	bool initialize();

	// Render all registered objects
	void render_scene(float deltaTime);

	// Updates the current scene
	void update_scene(float deltaTime);

	shared_ptr<directional_light> light;

private:

	// Private flag for current status of the manager
	bool _running;

	glm::vec3 _focus;

	// Private constructor (This SceneManager is a singleton)
	SceneManager() {};

	// Private copy constructor
	SceneManager(const SceneManager&);

	// Initialises the lighting for the scene
	bool initialize_lighting();

	// Private assignment operator
	void operator=(SceneManager&);

	void shutdown();
};