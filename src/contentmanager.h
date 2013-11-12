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
	void register_prop(mesh object);

	// Unregister object with scene manager
	void unregister_prop(mesh object);

	// Get object at index
	mesh get_prop_at(int index);

	// Get propList's size
	int prop_list_size();

private:

	// Private flag for current status of the manager
	bool _running;

	// Private collection of objects
	std::deque<mesh> prop_list;

	// Path to scene prop list
	string path;

	// Private constructor (This CameraManager is a singleton)
	ContentManager() {};

	// Private copy constructor
	ContentManager(const ContentManager&);

	// Load Content
	bool load_prop_list(string path);

	bool load_model(string modelPath, glm::vec3 modelPosition, glm::vec3 modelRotation, string modelVert, string modelFrag);

	bool load_scene_object(string path);

	mesh load_mesh(const aiMesh* pMesh, const aiScene* pScene);

	void apply_material(mesh model);

	// Private assignment operator
	void operator=(ContentManager&);

	void shutdown();
};