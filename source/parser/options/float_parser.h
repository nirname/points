#pragma once

void operator >> (const YAML::Node & option, float & parameter) {
	try {
		if(option.IsScalar()) {
			parameter = option.as<float>();
		}
	} catch(YAML::TypedBadConversion<float> & exception) {
	}
}

