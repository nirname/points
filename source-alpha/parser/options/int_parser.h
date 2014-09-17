#pragma once

void operator >> (const YAML::Node & option, int & parameter) {
	try {
		if(option.IsScalar()) {
			parameter = option.as<int>();
		}
	} catch(YAML::TypedBadConversion<int> & exception) {
	}
}

