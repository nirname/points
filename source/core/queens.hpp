#pragma once

#include "basic_screensaver.hpp"
#include "shape.hpp"
#include <list>
//#include <time.h> // time_t, struct tm, difftime, time, mktime

struct Queens : BasicScreensaver {

	Star shape;

	int field_size;
	int * queens;
	typedef std::list<int *> Solutions;
	Solutions solutions;
	Solutions::iterator current_solution;
	int last_update;

	Queens();
	~Queens();

	void display();
	void draw_letter(int x, int y, char letter);

	bool queen_in_field(int column, int row);
	bool can_put_a_queen(int column, int row);
	void put_a_queen(int column, int row);

	void save_solution();
	void next_solution();
	void print_queens(int column, int row);

};
