#ifndef GLOBAL_H
#define GLOBAL_H 1

// extern libraries

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <math.h>


#include <iostream>
//#include <unordered_map>
#include <string>
#include <functional>
#include <set>
#include <map>
#include <vector>
#include <list>

#if defined(_WIN32) && defined(__GNUC__)
	#include <gl/freeglut.h>
#elif defined(__linux__) && defined(__GNUC__)
	#include <GL/freeglut.h>
#endif

// own libraries

#include "declarations.h"

#include "graphics.h"
#include "logic.h"
#include "engine.h"
#include "controls.h"
#include "image.h"
#include "variables.h"
#include "params.h"



#endif
