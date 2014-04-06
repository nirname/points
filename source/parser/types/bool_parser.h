#pragma once

template<> void operator >> (const YAML::Node & option, bool & parameter) {
	if(option.IsScalar()) {
		std::string value = option.as<std::string>();
		if(value == std::string("on")) {
			parameter = true;
		} else {
			parameter = false;
		}
	}
}
