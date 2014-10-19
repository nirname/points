#include "screen.hpp"
#include "graphics.hpp"
#include "display.hpp"

#include <iostream>

Screen::Screen() {}

Screen::Screen(float _width, float _height) {
	set(_width, _height);
}

void Screen::set(float _width, float _height) {
	width = _width;
	height = _height;
	coordinates(0, width, 0, height);
	reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	std::cout << "* Screen is switched to " << width << ":" << height << std::endl;
}

void Screen::adjust() {
	set(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
