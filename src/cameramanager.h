#include <vector>
#include <render_framework\render_framework.h>

using namespace render_framework;
using namespace std;

class CameraManager {

public:
	// Destructor for CameraManager
	~CameraManager() { shutdown(); };

	// Gets singleton instance o 
	static CameraManager& get_instance()
	{
		static CameraManager instance;

		return instance;
	}

	// Gets the current running state of the CameraManger
	bool is_running() const { return _running; }

	shared_ptr<chase_camera> currentCamera;

	// Initialise the CameraManager
	bool initialize();

	// Update cameras
	void update(float deltaTime);

	// Register camera with CameraManager
	void registerCamera(chase_camera cam);

	// Unregister camera with CameraManager
	void unregisterCamera(int index);

	chase_camera getCameraAtIndex(int index);

	void setRenderCamera(chase_camera cam);

private:

	// Private flag for current status of the manager
	bool _running;

	// vector of cameras
	std::vector<chase_camera> cameras;

	// Private constructor (This CameraManager is a singleton)
	CameraManager() {};

	// Private copy constructor
	CameraManager(const CameraManager&);

	bool createCamera(chase_camera cam);

	// Private assignment operator
	void operator=(CameraManager&);

	void shutdown();

};