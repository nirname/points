#include "color.hpp"
#include "opengl.hpp"

#include <cmath>

/*struct RGB {
	unsigned int r;
	unsigned int g;
	unsigned int b;
};

struct HSV {
	double h;
	double s;
	double v;
};

static HSV rgb2hsv(RGB in) {
	HSV         out;
	double      min, max, delta;

	min = in.r < in.g ? in.r : in.g;
	min = min  < in.b ? min  : in.b;

	max = in.r > in.g ? in.r : in.g;
	max = max  > in.b ? max  : in.b;

	out.v = max;                                // v
	delta = max - min;
	if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
		out.s = (delta / max);                  // s
	} else {
		// if max is 0, then r = g = b = 0
		// s = 0, v is undefined
		out.s = 0.0;
		out.h = 0.0;                            // its now undefined
		return out;
	}
	if( in.r >= max )                         // > is bogus, just keeps compilor happy
		out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
	else
	if( in.g >= max )
		out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
	else
		out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

	out.h *= 60.0;                              // degrees

	if( out.h < 0.0 )
		out.h += 360.0;

	return out;
}

static RGB hsv2rgb(HSV in) {
	double      hh, p, q, t, ff;
	long        i;
	RGB         out;

	if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
		out.r = in.v;
		out.g = in.v;
		out.b = in.v;
		return out;
	}
	hh = in.h;
	if(hh >= 360.0) hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = in.v * (1.0 - in.s);
	q = in.v * (1.0 - (in.s * ff));
	t = in.v * (1.0 - (in.s * (1.0 - ff)));

	switch(i) {
	case 0:
		out.r = in.v;
		out.g = t;
		out.b = p;
		break;
	case 1:
		out.r = q;
		out.g = in.v;
		out.b = p;
		break;
	case 2:
		out.r = p;
		out.g = in.v;
		out.b = t;
		break;
	case 3:
		out.r = p;
		out.g = q;
		out.b = in.v;
		break;
	case 4:
		out.r = t;
		out.g = p;
		out.b = in.v;
		break;
	case 5:
	default:
		out.r = in.v;
		out.g = p;
		out.b = q;
		break;
	}
	return out;
}*/

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

Color::Color() {
	rgb(0, 0, 0);
}

Color::Color(int _red, int _green, int _blue) {
	rgb(_red, _green, _blue);
}

Color::Color(double _hue, double _saturation, double _value) {
	hsv(_hue, _saturation, _value);
}

void Color::use() const {
	glColor3ub(red, green, blue);
}

void Color::set(int _red, int _green, int _blue) {
	rgb(_red, _green, _blue);
}

void Color::set(double _hue, double _saturation, double _value) {
	hsv(_hue, _saturation, _value);
}

#include <iostream>

/// Set RGB values for color.
/// HSV values will be calculated at once.
///
void Color::rgb(int _red, int _green, int _blue) {

	double      min, max, delta;

	red = _red;
	green = _green;
	blue = _blue;

	std::cout << std::endl << "Color" << std::endl;
	std::cout << "  red " << red << std::endl;
	std::cout << "  green " << green << std::endl;
	std::cout << "  blue " << blue << std::endl;

	min = red < green ? red : green;
	min = min < blue ? min : blue;

	max = red > green ? red : green;
	max = max > blue ? max : blue;

	std::cout << "  max " << max << std::endl;
	std::cout << "  min " << min << std::endl;

	value = max / 255;
	delta = max - min;

	std::cout << "  value " << value << std::endl;
	std::cout << "  delta " << delta << std::endl;

	if(max > 0.0) {
		saturation = (delta / max);
		std::cout << "  saturation " << saturation << std::endl;
	} else {
		value = 0.0; saturation = 0.0; hue = 0.0;
		return;
	}

	std::cout << "  blue - green " << blue - green << std::endl;
	std::cout << "  red - blue " << red - blue << std::endl;
	std::cout << "  green - red " << green - red << std::endl;

	std::cout << "  blue - green / delta " << (blue - green) / delta << std::endl;
	std::cout << "  red - blue / delta " << (red - blue) / delta << std::endl;
	std::cout << "  green - red / delta " << (green - red) / delta  << std::endl;

	if(red >= max) {
		hue = ( green - blue ) / delta;        // between yellow & magenta
	} else if(green >= max) {
		hue = 2.0 + ( blue - red ) / delta;  // between cyan & yellow
	} else {
		hue = 4.0 + ( red - green ) / delta;  // between magenta & cyan
	}


	std::cout << "  hue " << hue << std::endl;
	hue *= 60.0;                              // degrees
	std::cout << "  hue * 60.0 " << hue << std::endl;

	if(hue < 0.0) {
		hue += 360.0;
	}

}

/// Set HSV values for color.
/// RGB values will be calculated at once.
///
void Color::hsv(double h, double s, double v) {

	int i;
	double f, p, q, t;

	if(h >= 360.0) { h = 0.0; }

	hue = h;
	saturation = s;
	value = v;

	v *= 255;

	if(s == 0) { // achromatic (grey)
		red = green = blue = v;
		return;
	}

	h /= 60.0; // sector from 0 to 5
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

/// Compare two colors by its RGB values
/// Returns true if colors are the same
///
bool Color::operator == (const Color & color) const {
	return (
		red == color.red &&
		green == color.green &&
		blue == color.blue
	);
}
