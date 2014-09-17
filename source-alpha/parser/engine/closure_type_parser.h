#pragma once

void operator >> (const std::string & value, CLOSURE_TYPE & _closure_type) {
	for(CLOSURE_TYPE i = NO_CLOSURE; i <= FULL_CLOSURE; i++) {
		if(value == lib::to_string(i)) {
			_closure_type = i;
			return;
		}
	}
}

void operator >> (const YAML::Node & option, CLOSURE_TYPE & parameter) {
	try {
		if(option.IsScalar()) {
			std::string value = option.as<std::string>();
			value >> parameter;
		}
	} catch(YAML::TypedBadConversion<std::string> & exception) {
	}
}
