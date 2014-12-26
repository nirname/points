#pragma once

#include "aspect_ratio.hpp"

struct Screen {

	int width, height;

	Screen();
	Screen(int _width, int _height);

	void set(int _width, int _height);
	void set(int _height, const AspectRatio & aspect_ratio);
	void set_coordinates();
	void adjust(int _height);

};
