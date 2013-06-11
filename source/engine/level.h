#ifndef LEVEL_H
#define LEVEL_H 1

namespace engine {

	struct Level {
		std::string name;
		bool load() {
			return true;
		}
	};

}

#endif
