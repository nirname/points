#pragma once

enum SCREENSAVER_KIND {
	NO_SCREENSAVER                   = 0x00,
	LIFE_SCREENSAVER                 = 0x01,
	QUEENS_SCREENSAVER               = 0x02,
	GEOGRAPHIC_EARTH_MAP_SCREENSAVER = 0x04,
	DAY_NIGHT_EARTH_MAP_SCREENSAVER  = 0x08,
	POLITICAL_EARTH_MAP_SCREENSAVER  = 0x10,
	TURTLE_SCREENSAVER               = 0x20,
	EQUALIZER_SCREENSAVER            = 0x40,
	TIMER_SCREENSAVER                = 0x80,
	RANDOM_SCREENSAVER               = 0xFF
};

SCREENSAVER_KIND & operator++(SCREENSAVER_KIND & _link, int) {
	const int i = static_cast<int>(_link);
	_link = static_cast<SCREENSAVER_KIND>((i == 0)? 1 : i << 1);
	return _link;
}

std::ostream & operator << (std::ostream & _ostream, const SCREENSAVER_KIND & _screensaver_kind) {
	switch(_screensaver_kind) {
		case NO_SCREENSAVER:                   _ostream << "No";             break;
		case LIFE_SCREENSAVER:                 _ostream << "Life";           break;
		case QUEENS_SCREENSAVER:               _ostream << "Queens";         break;
		case GEOGRAPHIC_EARTH_MAP_SCREENSAVER: _ostream << "Geographic map"; break;
		case DAY_NIGHT_EARTH_MAP_SCREENSAVER:  _ostream << "Day nigth map";  break;
		case POLITICAL_EARTH_MAP_SCREENSAVER:  _ostream << "Political map";  break;
		case TURTLE_SCREENSAVER:               _ostream << "Turtle";         break;
		case EQUALIZER_SCREENSAVER:            _ostream << "Equalizer";      break;
		case TIMER_SCREENSAVER:                _ostream << "Timer";          break;
		case RANDOM_SCREENSAVER:               _ostream << "Random";         break;
		default: {
			//_ostream << "Custom";
			_ostream << "Custom(";
				//YAML::Node node;
				for(SCREENSAVER_KIND k = LIFE_SCREENSAVER; k <= TIMER_SCREENSAVER; k++) {
					if(_screensaver_kind & k) {
						_ostream << " " << k << " ";
						//node.push_back << lib::to_string(k);
					}
				}
			_ostream << ")";
			break;
		}
	}
	return _ostream;
}


