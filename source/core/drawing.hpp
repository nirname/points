#pragma once

#include <string>
#include "opengl.hpp"

#include "font.hpp"
#include "bound.hpp"

const float DEG2RAD = 3.141592653589 / 180;

void write(std::string string, int x = 0, int y = 0, void * font = GLUT_BITMAP_9_BY_15);
void draw_text(std::string text, Font * _font = NULL);

void draw_block();
void draw_queen();
void draw_ngon(int angles = 5, int step_over = 1);
void draw_circle();

void draw_line(int x1, int y1, int x2, int y2);
void draw_grid(const Bound & _bound, int _step);
