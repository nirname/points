#include "library.hpp"

//#include <unistd.h>

// http://stackoverflow.com/questions/1528298/get-path-of-executable
/*
#if defined(_WIN32) && defined(__GNUC__)
#elif defined(__linux__) && defined(__GNUC__)
#endif

std::string application_path() {
	char buff[1024];
	ssize_t len = readlink("/proc/self/exe", buff, sizeof(buff) - 1);
	if (len != -1) {
		buff[len] = '\0';
		return std::string(buff);
	} else {
		return std::string(""); // handle error condition
	}
}
*/
