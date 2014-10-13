#pragma once

#if defined(_WIN32) && defined(__GNUC__)
	#include "dirent/windows/dirent.h"
#elif defined(__linux__) && defined(__GNUC__)
	#include "dirent/linux/dirent.h"
#endif
