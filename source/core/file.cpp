#include "file.hpp"
#include <cstring>

namespace file {

	/// Checks whether file has an extension or not.
	/**
		Works for 'c' strings
	*/
	bool has_extension(const char * name, const char * extension) {
		size_t name_length = strlen(name);
		size_t extension_length = strlen(extension);
		return
			name_length > extension_length &&
			strcmp(
				name + (name_length - extension_length) * sizeof(char),
				extension
			) == 0;
	}

	char * crop_extension(char * name, const char * extension) {
		//size_t extension_length = strlen(extension);
		//return name - extension_length * sizeof(char);
		return name;
	}

	/// Checks whether file has an extension or not.
	/**
		Works for 'c++' strings
	*/
	bool has_extension(std::string name, std::string extension) {
		return has_extension(name.c_str(), extension.c_str());
	}

	std::string crop_extension(std::string name, std::string extension) {
		return std::string(crop_extension(name.c_str(), extension.c_str()));
	}

}
