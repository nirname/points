#pragma once

enum APPLICATION_MODE {
	LOADING_MODE,
	FOREWORD_MODE,
	MENU_MODE,
	SCREENSAVER_MODE,
	COUNTDOWN_MODE,
	GAMEPLAY_MODE,
	INFORMATION_MODE, // Completion, Looser, Winner screen
	AFTERWORD_MODE,
};

std::ostream & operator << (std::ostream & _ostream, const APPLICATION_MODE _mode) {
	switch(_mode) {
		case LOADING_MODE: _ostream << "Loading"; break;
		case FOREWORD_MODE: _ostream << "Foreword"; break;
		case MENU_MODE: _ostream << "Menu"; break;
		case SCREENSAVER_MODE: _ostream << "Screensaver"; break;
		case COUNTDOWN_MODE: _ostream << "Countdown"; break;
		case GAMEPLAY_MODE: _ostream << "Gameplay"; break;
		case INFORMATION_MODE: _ostream << "Information"; break;
		case AFTERWORD_MODE: _ostream << "Afterword"; break;

	}
	return _ostream;
}
