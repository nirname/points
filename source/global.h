#ifndef GLOBAL_H
#define GLOBAL_H 1

// std headers

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>

#if defined(__linux__) && defined(__GNUC__)
	#include <cstring>
#endif

#include <stdio.h>
#include <math.h>

#include <time.h>

#include <string>
#include <functional>
#include <set>
#include <stack>
#include <map>
#include <vector>
#include <list>
#include <string.h>

#include <sys/types.h>

// external headers

#if defined(_WIN32) && defined(__GNUC__)
	#include "include/dirent/windows/dirent.h"
	#include <gl/freeglut.h>
#elif defined(__linux__) && defined(__GNUC__)
	#include "include/dirent/linux/dirent.h"
	#include <GL/freeglut.h>
#endif

#include "include/yaml-cpp/yaml.h"
#include "include/bitmap/bitmap_image.hpp"

// own headers

// constants

#include "constants.h"
#include "types.h"
#include "exception.h"
#include "program_mode.h"

#include "declarations.h"

#include "directory.h"

#include "mapping.h"
#include "library.h"

#include "letter.h"

#include "graphics.h"
#include "logic.h"
#include "engine.h"

#include "parser.h"

#include "menu.h"

#include "program.h"
#include "controls.h"
#include "image.h"
#include "variables.h"

#include "params.h"

#endif
