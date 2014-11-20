#include <string>

namespace file {

	bool has_extension(const char * name, const char * extension);
	bool has_extension(std::string name, std::string extension);

	char * crop_extension(char * name, const char * extension);
	std::string crop_extension(std::string name, std::string extension);

}
