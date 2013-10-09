#pragma once

#include <string>

namespace render_framework
{
	// Handy little define allowing debugging information to be displayed on a
	// debug build, or has no effect on a release build
#if defined(DEBUG) || defined(_DEBUG)
#define CHECK_GL_ERROR get_GL_error(__LINE__, __FILE__)
#define SET_DEBUG set_debug
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

	// Set debug function can be called to allow checking of memory leaks
	void set_debug();

	// Checks if a GL error has occurred, and prints a message if so
	bool get_GL_error(int line, const std::string& file);

#else
#define CHECK_GL_ERROR false
#define SET_DEBUG
#endif
}