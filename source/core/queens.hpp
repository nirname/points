#pragma once

#include "basic_screensaver.hpp"

struct Queens : BasicScreensaver {

	int size;
	int * field;

	Queens();
	~Queens();

	void display();

};
