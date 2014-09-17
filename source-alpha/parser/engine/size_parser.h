#pragma once

void operator >> (const YAML::Node & options, Size & size) {
	try {
		if(options.IsMap()) {
			if(options["width"] != NULL && options["height"] != NULL) {
				size.width = options["width"].as<int>();
				size.height = options["height"].as<int>();
			}
		} else if (options.IsSequence()) {
			if(options.size() == 1) {
				size.height = size.width = options[0].as<int>();
			} else if(options.size() == 2) {
				size.width = options[0].as<int>();
				size.height = options[1].as<int>();
			} else {
				std::cout << "Wrong number of arguments for size" << std::endl;
			}
		} else if (options.IsScalar()) {
			size.height = size.width = options.as<int>();
		} else {
			std::cout << "Size options should be scalar or map" << std::endl;
		}
	} catch(YAML::TypedBadConversion<int> & exception) {
		std::cout << "Size should be an integer " << std::endl;
		size.width = 1;
		size.height = 1;
	}
	if(size.width <= 0) {
		size.width = 1;
		std::cout << "Any size dimension should be greater than 0" << std::endl;
	}
	if(size.height <= 0) {
		size.height = 1;
		std::cout << "Any size dimension should be greater than 0" << std::endl;
	}
}
