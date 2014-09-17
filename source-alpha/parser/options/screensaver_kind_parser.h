#pragma once

void operator >> (std::string value, SCREENSAVER_KIND & _screensaver_kind) {
	SCREENSAVER_KIND result = NO_SCREENSAVER;
	if(value == lib::to_string(RANDOM_SCREENSAVER)) {
		_screensaver_kind = RANDOM_SCREENSAVER;
	} else {
		for(SCREENSAVER_KIND iterator = NO_SCREENSAVER; iterator <= TIMER_SCREENSAVER; iterator++) {
			if(value == lib::to_string(iterator)) {
				result = iterator;
				break;
			}
		}
	_screensaver_kind = SCREENSAVER_KIND(_screensaver_kind | result);
	}
}

void operator >> (const YAML::Node & option, SCREENSAVER_KIND & _screensaver_kind) {
	SCREENSAVER_KIND loaded_value = NO_SCREENSAVER;
	if(option.IsScalar()) {
		option.as<std::string>() >> loaded_value;
	} else if(option.IsSequence()) {
		for(YAML::const_iterator iterator = option.begin(); iterator != option.end(); ++iterator) {
			(iterator->as<std::string>()) >> loaded_value;
		}
	}
	_screensaver_kind = loaded_value;
}
