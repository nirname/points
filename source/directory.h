#pragma once

namespace Directory {

	// TODO: move this to level class
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

	void read(std::string directory) {
		DIR * dir;
		struct dirent * entry;
		if((dir = opendir(directory.c_str())) != NULL) {
			// print all the files and directories within directory
			while ((entry = readdir(dir)) != NULL) {
				// DT_DIR - directory, DT_REG - regular file
				if (entry->d_type == DT_REG && has_extension(entry->d_name, ".yaml")) {
					std::cout << "File: " << std::ends;
					printf("%s\n", entry->d_name);
					//printf("%zu - %s [%d] %d\n", entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen );
				}
			}
			closedir(dir);
		} else {
			std::cerr << "Could not open directory" << directory << std::endl;// could not open directory
			perror("");
			//return EXIT_FAILURE;
		}
	}

};
