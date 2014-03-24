#pragma once

enum SCREENSAVER_KIND {
	BLANK_SCREEN_SCREENSAVER = 0x00,
	LIFE_SCREENSAVER = 0x01,
	QUEENS_SCREENSAVER = 0x02,
	// TODO: unite them? slowly swap them
	GEOGRAPHIC_EARTH_MAP_SCREENSAVER = 0x04,
	DAY_NIGHT_EARTH_MAP_SCREENSAVER = 0x08,
	POLITICAL_EARTH_MAP_SCREENSAVER = 0x10,
	//
	TURTLE_SCREENSAVER = 0x20,
	EQUALIZER_SCREENSAVER = 0x40,
	TIMER_SCREENSAVER = 0x80,
	RANDOM_SCREENSAVER = 0xAA
};

std::ostream & operator << (std::ostream & _ostream, const SCREENSAVER_KIND _screensaver) {
	switch(_screensaver) {
		case BLANK_SCREEN_SCREENSAVER:         _ostream << "Blank screen";   break;
		case LIFE_SCREENSAVER:                 _ostream << "Live";           break;
		case QUEENS_SCREENSAVER:               _ostream << "Queens";         break;
		case GEOGRAPHIC_EARTH_MAP_SCREENSAVER: _ostream << "Deographic map"; break;
		case DAY_NIGHT_EARTH_MAP_SCREENSAVER:  _ostream << "Day nigth map";  break;
		case POLITICAL_EARTH_MAP_SCREENSAVER:  _ostream << "Political map";  break;
		case TURTLE_SCREENSAVER:               _ostream << "Turtle";         break;
		case EQUALIZER_SCREENSAVER:            _ostream << "Equalizer";      break;
		case TIMER_SCREENSAVER:                _ostream << "Timer";          break;
		case RANDOM_SCREENSAVER:               _ostream << "Random";         break;
	}
	return _ostream;
}
