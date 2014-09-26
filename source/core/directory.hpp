#pragma once

#include <string>
#include <list>

#if defined(_WIN32) && defined(__GNUC__)
	#include "dirent/windows/dirent.h"
#elif defined(__linux__) && defined(__GNUC__)
	#include "dirent/linux/dirent.h"
#endif

namespace directory {

	/// Reads directories or a files in `path` and fills in the specified list by names of the entries.
	/**
		'`dirent`' header is used.<br/>
		'`dirent`' structure contains:<br/>
			- d_type: DT_DIR - directory, DT_REG - regular file<br/>
			- d_name: name of a directory or a file<br/>
			- d_info<br/>
			- d_reclen<br/>
	*/
	bool read(const std::string & path, int type, std::list<std::string> & list, bool (*filter)(dirent *) = NULL);

};
