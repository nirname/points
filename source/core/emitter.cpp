#include "emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const SCREENSAVER_KIND & screensaver_kind) {
	switch(screensaver_kind) {
		case NO_SCREENSAVER:                   _ostream << "no";             break;
		case LIFE_SCREENSAVER:                 _ostream << "life";           break;
		case QUEENS_SCREENSAVER:               _ostream << "queens";         break;
		case GEOGRAPHIC_EARTH_MAP_SCREENSAVER: _ostream << "geographic map"; break;
		case DAY_NIGHT_EARTH_MAP_SCREENSAVER:  _ostream << "day nigth map";  break;
		case POLITICAL_EARTH_MAP_SCREENSAVER:  _ostream << "political map";  break;
		case TURTLE_SCREENSAVER:               _ostream << "turtle";         break;
		case EQUALIZER_SCREENSAVER:            _ostream << "equalizer";      break;
		case TIMER_SCREENSAVER:                _ostream << "timer";          break;
		case RANDOM_SCREENSAVER:               _ostream << "random";         break;
		default: {
			_ostream << "[";
				for(SCREENSAVER_KIND k = LIFE_SCREENSAVER; k <= TIMER_SCREENSAVER; k++) {
					if(screensaver_kind & k) {
						_ostream << " " << k << " ";
					}
				}
			_ostream << "]";
			break;
		}
	}
	return _ostream;
}

std::ostream & operator << (std::ostream & _ostream, const Color & color) {
	_ostream << "color("
		<< color.red << ", "
		<< color.green << ", "
		<< color.blue
	<< ")";
	return _ostream;
}
