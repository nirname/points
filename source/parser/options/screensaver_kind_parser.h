#pragma once

// TODO: remove this one?
void operator >> (std::string value, SCREENSAVER_KIND & _screensaver_kind) {
	SCREENSAVER_KIND result = NO_SCREENSAVER;
	for(SCREENSAVER_KIND iterator = NO_SCREENSAVER; iterator <= TIMER_SCREENSAVER; iterator++) {
		if(value == lib::to_string(iterator)) {
			result = iterator;
			break;
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

