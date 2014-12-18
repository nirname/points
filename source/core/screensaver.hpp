#pragma once

#include "screensaver_kind.hpp"
#include "basic_screensaver.hpp"
#include "timer.hpp"
#include "queens.hpp"

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
