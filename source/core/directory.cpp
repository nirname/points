#include "directory.hpp"

namespace directory {

	typedef bool (*Filter)(dirent *);

	bool read(const std::string & path, int type, std::list<std::string> & list, Filter filter) {
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
			//std::cout << "Could not open '" << path << "'" << std::ends;
			return false;
		}
	}

	/*bool check(const std::string & path, DIR ** dir) {
		return ((*dir) = opendir(path.c_str())) != NULL)
	}*/

}
