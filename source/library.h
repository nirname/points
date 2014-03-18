#pragma once

namespace lib {

	size_t strlen(const char * string) {
		#if defined(_WIN32) && defined(__GNUC__)
			return ::strlen(string);
		#elif defined(__linux__) && defined(__GNUC__)
			return std::strlen(string);
		#endif
	}

	template <typename T> std::string to_string (T value) {
		std::stringstream stream;
		stream << value;
		return stream.str();
	}

	void stage(const char * information) {
		std::cout << "\n\n" << information << std::endl;
	}
	
	std::string application_path() {
		char buff[1024];
		ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
		if (len != -1) {
			buff[len] = '\0';
			return std::string(buff);
		} else {
			
			/* handle error condition */
		}
}

}
