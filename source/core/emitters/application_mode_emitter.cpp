#include "application_mode_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const APPLICATION_MODE & application_mode) {
	switch(application_mode) {
		case LOADING_MODE:     _ostream << "loading mode";     break;
		case FOREWORD_MODE:    _ostream << "foreword mode";    break;
		case MENU_MODE:        _ostream << "menu mode";        break;
		case SCREENSAVER_MODE: _ostream << "screensaver mode"; break;
		case COUNTDOWN_MODE:   _ostream << "countdown mode";   break;
		case GAMEPLAY_MODE:    _ostream << "gameplay mode";    break;
		case INFORMATION_MODE: _ostream << "information mode"; break;
		case AFTERWORD_MODE:   _ostream << "afterword mode";   break;
	}
	return _ostream;
}
