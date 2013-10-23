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
	void render_scene();

	// Updates all registers objects in the scene
	void update(float deltaTime);

	// Register object with scene manager for rendering
	void registerObject(shared_ptr<mesh> object);

	// Unregister object with scene manager
	void unregisterObject(shared_ptr<mesh> object);

private:

	// Private flag for current status of the manager
	bool _running;

	// Private collection of objects
	std::deque<shared_ptr<mesh>> propList;

	// Private constructor (This SceneManager is a singleton)
	SceneManager() {};

	// Private copy constructor
	SceneManager(const SceneManager&);

	// Private assignment operator
	void operator=(SceneManager&);

	void shutdown();

};