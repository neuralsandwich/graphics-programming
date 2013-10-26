#include <vector>
#include <GLM\glm.hpp>
#include <render_framework\render_framework.h>

using namespace std;
using namespace render_framework;

class ContentManager {

public:
	// Destructor for CameraManager
	~ContentManager() { shutdown(); };

	// Gets singleton instance o 
	static ContentManager& get_instance()
	{
		static ContentManager instance;

		return instance;
	}

	// Gets the current running state of the renderer
	bool is_running() const { return _running; }

	// Initialise the CameraManager
	bool initialize();

	// Update cameras
	void update(float deltaTime);

	// Register object with scene manager for rendering
	void registerProp(mesh object);

	// Unregister object with scene manager
	void unregisterProp(mesh object);

	// Get object at index
	mesh getPropAt(int index);

	// Get propList's size
	int propListSize();

	// Load Content
	bool loadPropList(string path);

	void loadModel(string modelPath, glm::vec3 modelPosition);

private:

	// Private flag for current status of the manager
	bool _running;
	 
	// Private collection of objects
	std::deque<mesh> propList;

	// Path to scene prop list
	string path;

	// Private constructor (This CameraManager is a singleton)
	ContentManager() {};

	// Private copy constructor
	ContentManager(const ContentManager&);

	// Private assignment operator
	void operator=(ContentManager&);

	void shutdown();

};