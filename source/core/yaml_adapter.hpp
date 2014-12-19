#pragma once

#include "yaml.hpp"

typedef int (* YamlParser)(const YAML::Node & node);
typedef int (* YamlSerializer)(YAML::Node & node);

int load_yaml_file(std::string yaml_file_path, YamlParser parse_yaml);
int save_yaml_file(std::string yaml_file_path, YamlSerializer serialize_yaml);

/// Load an option depending on it's type
//
/// 0 - option is loaded
/// 1 - option is omitted, default value is used
/// 2 - option is wrong, default value is used
///
template<typename OptionType>
int load_yaml_option(OptionType & option, const YAML::Node & node, const char * key) {
	std::cout << "  " << key << ": " << std::ends;
	if(node[key]) {
		try {
			option = node[key].as<OptionType>();
			std::cout << "ok" << std::ends;
		} catch(YAML::TypedBadConversion<OptionType> & exception) {
			std::cout << "wrong value" << std::endl;
			return 2;
		}
	} else {
		std::cout << "default value" << std::endl;
		return 1;
	}
	std::cout << " - " << option << std::endl;
	return 0;
}
