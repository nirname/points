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
