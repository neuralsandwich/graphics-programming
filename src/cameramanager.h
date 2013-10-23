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

	// Gets the current running state of the renderer
	bool is_running() const { return _running; }

	// Initialise the CameraManager
	bool initialize();

private:

	// Private flag for current status of the manager
	bool _running;

	// Private constructor (This CameraManager is a singleton)
	CameraManager() {};

	// Private copy constructor
	CameraManager(const CameraManager&);

	// Private assignment operator
	void operator=(CameraManager&);

	void shutdown();

};