#pragma once

void operator >> (const YAML::Node & option, void (* & parameter)()) {
	if(option.IsScalar()) {
		std::string value = option.as<std::string>();
		if(value == std::string("square")) {
			parameter = graphics::square;
		} else if (value == std::string("circle")) {
			parameter = graphics::circle;
			//parameter = false;
		}
	}
}

