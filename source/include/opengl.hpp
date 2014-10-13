#pragma once

#if defined(_WIN32) && defined(__GNUC__)
	#include <gl/freeglut.h>
#elif defined(__linux__) && defined(__GNUC__)
	#include <GL/freeglut.h>
#endif
