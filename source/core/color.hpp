#pragma once

// simple colors
#define WHITE 255, 255, 255
#define GRAY 127, 127, 127
#define BLACK 0, 0, 0

#define RED 255, 0, 0
#define ORANGE 245, 121, 0
#define YELLOW 255, 255, 0
#define GREEN 0, 255, 0
#define AZURE 61, 222, 235
#define BLUE 0, 0, 255
#define VIOLET 255, 0, 255

// soft colors
#define SOFT_BLUE 17, 154, 255
#define SOFT_YELLOW 255, 232, 17
#define SOFT_GREEN 28, 174, 35
#define SOFT_RED 235, 80, 80
#define SOFT_VIOLET 175, 0, 185

// light colors
#define LIGHT_GRAY 192, 192, 192
#define LIGHT_VIOLET 173, 127, 168

// dark colors
#define DARK_VIOLET 48, 14, 57
#define DARK_GRAY 63, 63, 63

struct Color {

	unsigned int red, green, blue;

	Color();
	Color(int _red, int _green, int _blue);
	Color(double hue, double saturation, double value);

	void use();
	void rgb(int _red, int _green, int _blue);
	void hsv(double hue, double saturation, double value);

};

extern Color default_color;
