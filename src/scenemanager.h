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
	void renderScene(float deltaTime);

	// Updates the current scene
	void updateScene(float deltaTime);

	shared_ptr<directional_light> light;

private:

	// Private flag for current status of the manager
	bool _running;

	// Private constructor (This SceneManager is a singleton)
	SceneManager() {};

	// Private copy constructor
	SceneManager(const SceneManager&);

	// Private assignment operator
	void operator=(SceneManager&);

	void shutdown();

};