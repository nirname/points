#pragma once

#include "yaml.hpp"

typedef int (* YamlHandler)(YAML::Node & node);

int load_yaml_file(std::string yaml_file_path, YamlHandler parse_yaml);
int save_yaml_file(std::string yaml_file_path, YamlHandler serialize_yaml);

template<typename OptionType>
int parse_yaml_option(OptionType & option, const YAML::Node & node, const char * key);
