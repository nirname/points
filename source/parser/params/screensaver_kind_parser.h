#pragma once

void operator >> (std::string value, SCREENSAVER_KIND & _screensaver_kind) {
	SCREENSAVER_KIND result = NO_SCREENSAVER;
	for(SCREENSAVER_KIND k = NO_SCREENSAVER; k <= TIMER_SCREENSAVER; k++) {
		if(value == lib::to_string(k)) {
			result = k; break;
		}
	}
	_screensaver_kind = SCREENSAVER_KIND(_screensaver_kind | result);
}

void operator >> (const YAML::Node & option, SCREENSAVER_KIND & _screensaver_kind) {
	if(option.IsScalar()) {
		option.as<std::string>() >> _screensaver_kind;
	} else if(option.IsSequence()) {
		for(YAML::const_iterator iterator = option.begin(); iterator != option.end(); ++iterator) {
			(iterator->as<std::string>()) >> _screensaver_kind;
		}
	}
}

