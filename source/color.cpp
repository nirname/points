#include "color.hpp"

Color::Color(positive _red, positive _green, positive _blue):
	red(_red), green(_green), blue(_blue)
{}

Color::Color():
	red(0), green(0), blue(0)
{}

void Color::use() {
	//glColor3ub(red, green, blue);
}

void Color::set(positive _red, positive _green, positive _blue) {
	red = _red;
	green = _green;
	blue = _blue;
}
