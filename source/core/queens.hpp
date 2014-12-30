#pragma once

#include "basic_screensaver.hpp"
#include "shape.hpp"

struct Queens : BasicScreensaver {

	Star shape;

	int field_size;
	int * queens;

	Queens();
	~Queens();

	void display();
	bool queen_in_field(int column, int row);
	bool put_a_queen(int column, int row);
	bool can_put_a_queen(int column, int row);

};
