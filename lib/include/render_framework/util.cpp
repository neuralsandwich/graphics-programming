#pragma comment(lib, "Glu32")

#include "util.h"
#define GLFW_INCLUDE_GLU
#include <GL\glfw3.h>
#include <iostream>

namespace render_framework
{
	void set_debug()
	{
#if defined(DEBUG) || defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	}

	bool get_GL_error(int line, const std::string& file)
	{
		GLenum error = glGetError();
		if (error)
		{
			std::cerr << "OpenGL Error: " << gluErrorString(error) << " at line "
					  << line << " in file " << file << std::endl;
			return true;
		}
		return false;
	}
}