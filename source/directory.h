#pragma once

namespace Directory {

	// `dirent` structure:
	//
	// d_type: DT_DIR - directory, DT_REG - regular file
	// d_name: name of a directory or a file
	// d_info
	// d_reclen

	// Reads directories or a files in `path`
	// and fills in the specified list by names of the entries
	//
	bool read(const std::string & path, int type, lines & list, bool (*filter)(dirent *) = NULL) {
		DIR * dir;
		dirent * entry;
		if((dir = opendir(path.c_str())) != NULL) {
			while ((entry = readdir(dir)) != NULL) {
				if (entry->d_type == type) {
					if(filter == NULL || filter(entry)) {
						list.push_back(std::string(entry->d_name));
					}
				}
			}
			closedir(dir);
			return true;
		} else {
			std::cout << "Could not open '" << path << "'" << std::ends;
			return false;
		}
	}

};

namespace File {

	// Checkes whether file has an extension or not
	//
	bool has_extension(const char * name, const char * extension)
	{
		size_t name_length = lib::strlen(name);
		size_t extension_length = lib::strlen(extension);
		return
			name_length > extension_length &&
			strcmp(
				name + (name_length - extension_length) * sizeof(char),
				extension
			) == 0;
	}
	
	bool has_extension(std::string name, std::string extension){
		return has_extension(name.c_str(), extension.c_str());
	}

}
