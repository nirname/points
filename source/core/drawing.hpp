#pragma once

#include <string>
#include "opengl.hpp"

#include "font.hpp"
#include "bound.hpp"

typedef void (*DrawingFunction)();
extern DrawingFunction default_shape;

enum DISPLAY_LISTS_IDS {
	CIRCLE_DISPLAY_LIST = 1
};

const float DEG2RAD = 3.141592653589 / 180;

void write(std::string string, int x = 0, int y = 0, void * font = GLUT_BITMAP_9_BY_15);
void write(std::string text, int x, int y, Font * _font);

void square();
void point();
void ngon(int angles = 5, int step_over = 1);
void circle();
void star();
void david();

void line(int x1, int y1, int x2, int y2);
void grid(const Bound & _bound, int _step);

void display_at(void (* displayer)(), int x, int y);
