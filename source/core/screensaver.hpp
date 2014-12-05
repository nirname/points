#pragma once

#include <cstdlib>
#include "drawing.hpp"
#include "color.hpp"

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

SCREENSAVER_KIND & operator ++ (SCREENSAVER_KIND & screensaver_kind, int);

struct BasicScreensaver {

	int width;
	int height;

	BasicScreensaver();
	virtual ~BasicScreensaver() = 0;

	virtual void display() = 0;

};

struct Screensaver {

	Screensaver();
	~Screensaver();

	BasicScreensaver * basic_screensaver;

	bool load(const SCREENSAVER_KIND & kind);
	bool is_loaded();
	void skip();

	void display();

	int width();
	int height();

};

/*struct Queens : BasicScreensaver {

	int size;
	int * field;

	Queens();
	~Queens();

	void display();

};*/

#include <time.h>       /* time_t, struct tm, difftime, time, mktime */

struct Timer : BasicScreensaver {

	Color color;
	double hue;
	int prev;

	time_t timer;
	tm * timeinfo;

	Timer();
	~Timer();

	double calculate_hue();
	void display();

};
