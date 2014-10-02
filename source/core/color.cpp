#include "color.hpp"
#include "opengl.hpp"

Color::Color():
	red(0), green(0), blue(0)
{}

Color::Color(unsigned int _red, unsigned int _green, unsigned int _blue):
	red(_red), green(_green), blue(_blue)
{}

void Color::use() {
	glColor3ub(red, green, blue);
}

void Color::set(unsigned int _red, unsigned int _green, unsigned int _blue) {
	red = _red;
	green = _green;
	blue = _blue;
}
