#pragma once

#include "basic_screensaver.hpp"

#include "color.hpp"
#include <time.h> // time_t, struct tm, difftime, time, mktime

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
