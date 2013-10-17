#ifndef GLOBAL_H
#define GLOBAL_H 1

// extern libraries

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
//#include <iomanip>

#if defined(__linux__) && defined(__GNUC__)
	#include <cstring>
#endif

#include <stdio.h>
#include <math.h>

#include <time.h>

//#include <unordered_map>
#include <string>
#include <functional>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <string.h>

#include <sys/types.h>

#if defined(_WIN32) && defined(__GNUC__)
		#include "include/dirent/windows/dirent.h"
	#include <gl/freeglut.h>
	//#define BASE_MATRIX_MODE GL_MODELVIEW
#elif defined(__linux__) && defined(__GNUC__)
	#include "include/dirent/linux/dirent.h"
	#include <GL/freeglut.h>
	//#define BASE_MATRIX_MODE GL_PROJECTION
#endif
#define BASE_MATRIX_MODE GL_MODELVIEW

#include "include/yaml-cpp/yaml.h"

// own libraries

#include "types.h"
#include "exception.h"

#include "declarations.h"

#include "mapping.h"
#include "library.h"

#include "letter.h"

#include "graphics.h"
#include "logic.h"
#include "engine.h"

#include "parser.h"

#include "controls.h"
#include "image.h"
#include "variables.h"
#include "params.h"

#endif
