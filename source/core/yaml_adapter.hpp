#pragma once

#include "yaml.hpp"
#include <fstream>

/// Load YAML file
//
/// 0 - everything is ok
/// 1 - with omitted values
/// 2 - with wrong values
/// 3 - wrong format / is not a map
/// 4 - syntax errors inside
/// 5 - file not found
///
template<typename YamlLoader>
int load_yaml_file(std::string yaml_file_path, YamlLoader load_yaml) {
	std::cout << "Loading file '" + yaml_file_path + "': " << std::ends;
	try {
		YAML::Node node = YAML::LoadFile(yaml_file_path.c_str());
		if(node.IsMap()) {
			std::cout << "ok" << std::endl;
			return load_yaml(node);
		} else {
			std::cout << "file is not a map" << std::endl;
			return 3;
		}
	} catch (YAML::ParserException & exception) {
		std::cout << "syntax errors" << std::endl;
		return 4;
	} catch (YAML::BadFile) {
		std::cout << "file does not exist or corrupted" << std::endl;
		return 5;
	}
}

/// Save YAML file
//
/// 0 - everything is ok
/// 1 - file was not saved
///
template<typename YamlSerializer>
int save_yaml_file(std::string yaml_file_path, YamlSerializer serialize_yaml) {
	std::cout << "Saving file '" + yaml_file_path + "': " << std::ends;

	YAML::Emitter yaml;

	YAML::Node node;
	serialize_yaml(node);
	yaml << node;

	std::ofstream file(yaml_file_path.c_str());
	if(file.good() && file.is_open()) {
		file << yaml.c_str();
		std::cout << "yes" << std::endl;
		file.close();
	} else {
		std::cout << "no" << std::endl;
		return 1;
	}

	return 0;
}

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
