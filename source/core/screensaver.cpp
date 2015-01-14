#include "screensaver.hpp"

#include "timer.hpp"
#include "queens.hpp"

#include "drawing.hpp"
#include "library.hpp"
#include "emitter.hpp"

SCREENSAVER_KIND & operator ++ (SCREENSAVER_KIND & screensaver_kind, int) {
	int i = static_cast<int>(screensaver_kind);
	screensaver_kind = static_cast<SCREENSAVER_KIND>((i == 0)? 1 : i << 1);
	return screensaver_kind;
}

Screensaver::Screensaver() {
	basic_screensaver = NULL;
}

Screensaver::~Screensaver() {
	skip();
}

bool Screensaver::load(const SCREENSAVER_KIND & kind) {
	skip();
	//SCREENSAVER_KIND
	//int number = rand() % 8 + 1;
	SCREENSAVER_KIND choice = kind;
	switch(choice) {
		case LIFE_SCREENSAVER:                 break;
		case QUEENS_SCREENSAVER: basic_screensaver = new Queens(); break;
		case GEOGRAPHIC_EARTH_MAP_SCREENSAVER: break;
		case DAY_NIGHT_EARTH_MAP_SCREENSAVER:  break;
		case POLITICAL_EARTH_MAP_SCREENSAVER:  break;
		case TURTLE_SCREENSAVER:               break;
		case EQUALIZER_SCREENSAVER:            break;
		case TIMER_SCREENSAVER: basic_screensaver = new Timer(); break;
		default: return false;
	}
	return true;
}

bool Screensaver::is_loaded() {
	return basic_screensaver != NULL;
}

void Screensaver::skip() {
	if(is_loaded()) {
		delete basic_screensaver;
		basic_screensaver = NULL;
	}
}

void Screensaver::display() {
	if(is_loaded()) {
		basic_screensaver->display();
	}
}

int Screensaver::width() {
	if(is_loaded()) {
		return basic_screensaver->size.width;
	} else {
		return 0;
	}
}

int Screensaver::height() {
	if(is_loaded()) {
		return basic_screensaver->size.height;
	} else {
		return 0;
	}
}
