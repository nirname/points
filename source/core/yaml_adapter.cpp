#include "yaml_adapter.hpp"

template<>
int load_yaml_option<YAML::Node>
(YAML::Node & option, const YAML::Node & node, const char * key) {
	std::cout << "  " << key << ": " << std::ends;
	if(node[key]) {
		option = node[key];
		std::cout << "ok" << std::endl;
		return 0;
	} else {
		std::cout << "default value" << std::endl;
		return 1;
	}
}
