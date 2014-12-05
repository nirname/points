#include "color.hpp"
#include "opengl.hpp"

#include <cmath>

namespace pallete {
	const Color black(BLACK);
	const Color dark_gray(DARK_GRAY);
	const Color gray(GRAY);
	const Color light_gray(LIGHT_GRAY);
	const Color white(WHITE);

	const Color red(RED);
	const Color red_orange(RED_ORANGE);
	const Color orange(ORANGE);
	const Color yellow_orange(YELLOW_ORANGE);
	const Color yellow(YELLOW);
	const Color yellow_green(YELLOW_GREEN);
	const Color green(GREEN);
	const Color sea_green(SEA_GREEN);
	const Color blue_green(BLUE_GREEN);
	const Color cyan(CYAN);
	const Color sky_blue(SKY_BLUE);
	const Color soft_blue(SOFT_BLUE);
	const Color blue(BLUE);
	const Color purple(PURPLE);
	const Color violet(VIOLET);
	const Color red_violet(RED_VIOLET);
}

Color default_color(BLACK);

Color::Color():
	red(0), green(0), blue(0)
{}

Color::Color(int _red, int _green, int _blue) {
	rgb(_red, _green, _blue);
}

Color::Color(double hue, double saturation, double value) {
	hsv(hue, saturation, value);
}

void Color::use() const {
	glColor3ub(red, green, blue);
}

void Color::set(int _red, int _green, int _blue) {
	rgb(_red, _green, _blue);
}

void Color::set(double hue, double saturation, double value) {
	hsv(hue, saturation, value);
}

void Color::rgb(int _red, int _green, int _blue) {
	red = _red;
	green = _green;
	blue = _blue;
}

void Color::hsv(double h, double s, double v) {

	int i;
	double f, p, q, t;

	v *= 255;

	if(s == 0) { // achromatic (grey)
		red = green = blue = v;
		return;
	}

	if(h >= 360.0) h = 0.0;

	h /= 60.0; // sector 0 to 5
	i = floor( h );
	f = h - i; // factorial part of h
	p = v * ( 1.0 - s );
	q = v * ( 1.0 - s * f );
	t = v * ( 1.0 - s * ( 1.0 - f ) );

	switch( i ) {
		case 0: red = v; green = t; blue = p; break;
		case 1: red = q; green = v; blue = p; break;
		case 2: red = p; green = v; blue = t; break;
		case 3: red = p; green = q; blue = v; break;
		case 4: red = t; green = p; blue = v; break;
		case 5: default: red = v; green = p; blue = q; break;
	}
}

bool Color::operator == (const Color & color) const {
	return
		red == color.red &&
		green == color.green &&
		blue == color.blue;
}
