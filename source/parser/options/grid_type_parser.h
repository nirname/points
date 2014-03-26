#pragma once

void operator >> (const YAML::Node & option, GRID_TYPE & parameter) {
	try {
		if(option.IsScalar()) {
			std::string value = option.as<std::string>();
			for(GRID_TYPE iterator = SQUARE_GRID; iterator <= CORNER_BASED_HEXAGON_GRID; iterator++) {
				if(value == lib::to_string(iterator)) {
					parameter = iterator;
					return;
				}
			}
		}
	} catch(YAML::TypedBadConversion<std::string> & exception) {
	}
}

