#pragma once

template<typename T> void operator >> (const YAML::Node & option, T & parameter) {
	try {
		if(option.IsScalar()) {
			parameter = option.as<T>();
		}
	} catch(YAML::TypedBadConversion<T> & exception) {
	}
}
