#pragma once

#include <cstdlib>
#include "drawing.hpp"

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

struct Screensaver {

	SCREENSAVER_KIND kind;
	int width;
	int height;

	virtual void display();
	void skip();

};

struct Queens : Screensaver {

	int size;
	int * field;

	Queens();
	~Queens();

	void display();

};
