#pragma once

#if defined(_WIN32) && defined(__GNUC__)
	#include "include/dirent/windows/dirent.h"
	#include <gl/freeglut.h>
#elif defined(__linux__) && defined(__GNUC__)
	#include "include/dirent/linux/dirent.h"
	#include <GL/freeglut.h>
#endif

#include "include/yaml-cpp/yaml.h"
//#include "include/bitmap/bitmap_image.hpp"
#include "include/easy-bmp/EasyBMP.h"
#include "include/window_pos.h"
