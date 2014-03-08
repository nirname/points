#pragma once

namespace Directory {

	bool read(std::string directory, int type, std::list<std::string> * list) {
		DIR * dir;
		struct dirent * entry;
		if((dir = opendir(directory.c_str())) != NULL) {
			while ((entry = readdir(dir)) != NULL) {
				if (entry->d_type == type) {
					list->push_back(std::string("hello"));
				}
				// DT_DIR - directory, DT_REG - regular file
				/*if (entry->d_type == DT_REG && has_extension(entry->d_name, ".yaml")) {
					std::cout << "File: " << std::ends;
					printf("%s\n", entry->d_name);
					//printf("%zu - %s [%d] %d\n", entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen );
				}*/
			}
			closedir(dir);
			return true;
		} else {
			/*std::cerr << "Could not open directory" << directory << std::endl;
			perror("");*/
			//return EXIT_FAILURE;
			return false;
		}
	}

};

namespace File {

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

}
