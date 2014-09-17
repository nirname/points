#pragma once

struct Screensaver {

	SCREENSAVER_KIND kind;

	void display() {
		graphics::write(lib::to_string(kind));
	}
	/*void display() {
		switch(_screensaver) {
		case NO_SCREENSAVER:                   break;
		case LIFE_SCREENSAVER:                 break;
		case QUEENS_SCREENSAVER:               break;
		case GEOGRAPHIC_EARTH_MAP_SCREENSAVER: break;
		case DAY_NIGHT_EARTH_MAP_SCREENSAVER:  break;
		case POLITICAL_EARTH_MAP_SCREENSAVER:  break;
		case TURTLE_SCREENSAVER:               break;
		case EQUALIZER_SCREENSAVER:            break;
		case TIMER_SCREENSAVER:                break;
		case RANDOM_SCREENSAVER:               break;
	}*/
	
};


std::ostream & operator << (std::ostream & _ostream, const Screensaver & _screensaver) {
	_ostream << _screensaver.kind;
	return _ostream;
}

