#include "screen.hpp"
#include "graphics.hpp"
#include "display.hpp"

#include <cmath>

#include <iostream>

AspectRatio::AspectRatio() :
	width(16), height(9)
{}

AspectRatio::AspectRatio(int _width, int _height) :
	width(_width), height(_height)
{}

float AspectRatio::aspect() const {
	return (float)width / (float)height;
}

Screen::Screen() {}

Screen::Screen(float _width, float _height) {
	set(_width, _height);
}

void Screen::set_coordinates() {
	coordinates(0, width, 0, height);
	reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	std::cout << "* Screen is switched to " << width << ":" << height << std::endl;
}

void Screen::set(float _width, float _height) {
	width = round(_width);
	height = round(_height);
	set_coordinates();
}

void Screen::set(float lines, const AspectRatio & aspect_ratio) {
	height = round(lines);
	width = round(height * aspect_ratio.aspect());
	set_coordinates();
}

void Screen::adjust(int lines) {
	int _window_width = glutGet(GLUT_WINDOW_WIDTH);
	int _window_height = glutGet(GLUT_WINDOW_HEIGHT);
	std::cout
		<< "* Adjust screen to "
		<< _window_width << ":" << _window_height << std::endl;
	AspectRatio aspect_ratio(_window_width, _window_height);
	set(lines, aspect_ratio);
}
