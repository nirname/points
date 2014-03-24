#pragma once

void operator >> (std::string & value, SCREENSAVER_KIND & _screensaver) {
	if(value == "blank") {
		_screensaver = BLANK_SCREEN_SCREENSAVER;
	} else if(value == "life") {
		_screensaver = LIFE_SCREENSAVER;
	} else if(value == "queens") {
		_screensaver = QUEENS_SCREENSAVER;
	} else if(value == "geographic_map") {
		_screensaver = GEOGRAPHIC_EARTH_MAP_SCREENSAVER;
	} else if(value == "day_night_map") {
		_screensaver = DAY_NIGHT_EARTH_MAP_SCREENSAVER;
	} else if(value == "political_map") {
		_screensaver = POLITICAL_EARTH_MAP_SCREENSAVER;
	} else if(value == "turtle") {
		_screensaver = TURTLE_SCREENSAVER;
	} else if(value == "equalizer") {
		_screensaver = EQUALIZER_SCREENSAVER;
	} else if(value == "timer") {
		_screensaver = TIMER_SCREENSAVER;
	//} else if(value == "random") {
		//_screensaver = RANDOM_SCREENSAVER;
	} else {
		// default
	}
}

