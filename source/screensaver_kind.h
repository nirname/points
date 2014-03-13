#pragma once

enum SCREENSAVER_KIND {
	NO_SCREENSAVER = 0x00,
	LIVE_SCREENSAVER = 0x01,
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
		case NO_SCREENSAVER:     _ostream << "no screensaver";               break;
		case LIVE_SCREENSAVER:   _ostream << "live";                         break;
		case QUEENS_SCREENSAVER: _ostream << "queens";                       break;
		case GEOGRAPHIC_EARTH_MAP_SCREENSAVER: _ostream << "geographic map"; break;
		case DAY_NIGHT_EARTH_MAP_SCREENSAVER:  _ostream << "day nigth map";  break;
		case POLITICAL_EARTH_MAP_SCREENSAVER:  _ostream << "political map";  break;
		case TURTLE_SCREENSAVER:    _ostream << "turtle";                    break;
		case EQUALIZER_SCREENSAVER: _ostream << "equalizer";                 break;
		case TIMER_SCREENSAVER:     _ostream << "timer";                     break;
		case RANDOM_SCREENSAVER:    _ostream << "no screensaver";            break;
	}
	return _ostream;
}
