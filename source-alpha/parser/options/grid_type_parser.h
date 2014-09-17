#pragma once

void operator >> (const std::string & value, GRID_TYPE & _grid_type) {
	for(GRID_TYPE iterator = SQUARE_GRID; iterator <= CORNER_BASED_HEXAGON_GRID; iterator++) {
		if(value == lib::to_string(iterator)) {
			_grid_type = iterator;
			return;
		}
	}
}

void operator >> (const YAML::Node & option, GRID_TYPE & parameter) {
	try {
		if(option.IsScalar()) {
			std::string value = option.as<std::string>();
			value >> parameter;
		}
	} catch(YAML::TypedBadConversion<std::string> & exception) {
	}
}

