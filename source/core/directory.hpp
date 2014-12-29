#pragma once

#include <string>
#include <list>

#include "dirent.hpp"

namespace directory {

	typedef bool (*Filter)(dirent *);

	/// Reads directories or a files in `path` and fills in the specified list by names of the entries.
	/**
		'`dirent`' header is used.<br/>
		'`dirent`' structure contains:<br/>
			- d_type: DT_DIR - directory, DT_REG - regular file<br/>
			- d_name: name of a directory or a file<br/>
			- d_info<br/>
			- d_reclen<br/>
	*/
	bool read(const std::string & path, int type, std::list<std::string> & list, Filter filter = NULL);

};
