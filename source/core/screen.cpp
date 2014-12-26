#include "screen.hpp"
#include "graphics.hpp"
#include "display.hpp"

#include <cmath>

#include <iostream>

Screen::Screen() {}

Screen::Screen(int _width, int _height) {
	set(_width, _height);
}

void Screen::set_coordinates() {
	coordinates(0, width, 0, height);
	reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	std::cout << "* Screen is switched to " << width << ":" << height << std::endl;
}

void Screen::set(int _width, int _height) {
	width = _width;
	height = _height;
	set_coordinates();
}

void Screen::set(int _height, const AspectRatio & aspect_ratio) {
	height = _height;
	width = round(height * aspect_ratio.aspect());
	set_coordinates();
}

void Screen::adjust(int _height) {
	int _window_width = glutGet(GLUT_WINDOW_WIDTH);
	int _window_height = glutGet(GLUT_WINDOW_HEIGHT);
	std::cout
		<< "* Adjust screen to "
		<< _window_width << ":" << _window_height << std::endl;
	AspectRatio aspect_ratio(_window_width, _window_height);
	set(_height, aspect_ratio);
}
