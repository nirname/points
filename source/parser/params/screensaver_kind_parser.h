#pragma once

void operator >> (std::string & value, SCREENSAVER_KIND & _screensaver) {
	if(value == "no") {
		_screensaver = NO_SCREENSAVER;
	} else if(value == "no") {
		_screensaver = LIVE_SCREENSAVER;
	} else if(value == "queens") {
		_screensaver = QUEENS_SCREENSAVER;
	/*} else if(value == "geographic_map") {
		_screensaver = GEOGRAPHIC_EARTH_MAP_SCREENSAVER;
	} else if(value == "day_night_map") {
		_screensaver = DAY_NIGHT_EARTH_MAP_SCREENSAVER;
	} else if(value == "political_map") {
		_screensaver = POLITICAL_EARTH_MAP_SCREENSAVER;*/
	} else if(value == "turtle") {
		_screensaver = TURTLE_SCREENSAVER;
	} else if(value == "equalizer") {
		_screensaver = EQUALIZER_SCREENSAVER;
	} else if(value == "timer") {
		_screensaver = TIMER_SCREENSAVER;
	} else if(value == "random") {
		_screensaver = RANDOM_SCREENSAVER;
	} else {
		// default
	}
}

/*
#pragma once

enum SCREENSAVER_KIND {
	NO_SCREENSAVER = 0x00,
	LIVE_SCREENSAVER = 0x01,
	QUEENS_SCREENSAVER = 0x02,
	GEOGRAPHIC_EARTH_MAP_SCREENSAVER = 0x04,
	DAY_NIGHT_EARTH_MAP_SCREENSAVER = 0x08,
	POLITICAL_EARTH_MAP_SCREENSAVER = 0x10,
	TURTLE_SCREENSAVER = 0x20,
	EQUALIZER_SCREENSAVER = 0x40,
	TIMER_SCREENSAVER = 0x80,
	RANDOM_SCREENSAVER = 0xAA
};
*/
