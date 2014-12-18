#pragma once

#define BLACK       0.0, 0.0, 0.00
#define DARK_GRAY   0.0, 0.0, 0.25
#define GRAY        0.0, 0.0, 0.50
#define LIGHT_GRAY  0.0, 0.0, 0.75
#define WHITE       0.0, 0.0, 1.00

#define RED             0.0, 1.0, 1.0
#define RED_ORANGE     30.0, 1.0, 1.0
#define ORANGE         45.0, 1.0, 1.0
#define YELLOW_ORANGE  55.0, 1.0, 1.0
#define YELLOW         60.0, 1.0, 1.0
#define YELLOW_GREEN   75.0, 1.0, 1.0
#define GREEN         120.0, 1.0, 1.0
#define SEA_GREEN     150.0, 1.0, 1.0
#define BLUE_GREEN    165.0, 1.0, 1.0
#define CYAN          180.0, 1.0, 1.0
#define SKY_BLUE      195.0, 1.0, 1.0
#define SOFT_BLUE     210.0, 1.0, 1.0
#define BLUE          240.0, 1.0, 1.0
#define PURPLE        285.0, 1.0, 1.0
#define VIOLET        300.0, 1.0, 1.0
#define RED_VIOLET    330.0, 1.0, 1.0

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

struct Color {

	unsigned int red, green, blue;

	Color();
	Color(int _red, int _green, int _blue);
	Color(double hue, double saturation, double value);

	void use() const;

	void set(int _red, int _green, int _blue);
	void set(double hue, double saturation, double value);

	void rgb(int _red, int _green, int _blue);
	void hsv(double hue, double saturation, double value);

	bool operator == (const Color & color) const;

};

namespace pallete {
	extern const Color black;
	extern const Color dark_gray;
	extern const Color gray;
	extern const Color light_gray;
	extern const Color white;

	extern const Color red;
	extern const Color red_orange;
	extern const Color orange;
	extern const Color yellow_orange;
	extern const Color yellow;
	extern const Color yellow_green;
	extern const Color green;
	extern const Color sea_green;
	extern const Color blue_green;
	extern const Color cyan;
	extern const Color sky_blue;
	extern const Color soft_blue;
	extern const Color blue;
	extern const Color purple;
	extern const Color violet;
	extern const Color red_violet;
}

extern Color default_color;
