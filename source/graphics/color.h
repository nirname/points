#ifndef COLOR_H
#define COLOR_H 1

//#define BLUE 20, 73, 233 // blue
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0
#define BLUE 17, 154, 255
#define YELLOW 255, 232, 17
#define GREEN 28, 174, 35
#define RED 235, 80, 80
#define AZURE 61, 222, 235
#define VIOLET 175, 0, 185
#define GRAY 127, 127, 127
#define ORANGE 245, 121, 0
#define DARK_GRAY 63, 63, 63
#define LIGHT_GRAY 192, 192, 192

//GLfloat glutGetColor(int cell, int component);
//void glutSetColor(int cell, GLfloat red, GLfloat green, GLfloat blue);

namespace graphics {

	/*enum COLOR {
		BLACK_COLOR = 10,
		RED_COLOR,
		GREEN_COLOR,
		BLUE_COLOR,
		YELLOW_COLOR,
		MAGENTA_COLOR,
		CYAN_COLOR,
		WHITE_COLOR
	};*/

	/*void load_palette() {
		glutSetColor((int)BLACK_COLOR,   0.0, 0.0, 0.0);
		glutSetColor((int)RED_COLOR,     1.0, 0.0, 0.0);
		glutSetColor(12,   0.0, 1.0, 0.0);
		glutSetColor((int)BLUE_COLOR,    0.0, 0.0, 1.0);
		glutSetColor((int)YELLOW_COLOR,  1.0, 1.0, 0.0);
		glutSetColor((int)MAGENTA_COLOR, 1.0, 0.0, 1.0);
		glutSetColor((int)CYAN_COLOR,    0.0, 1.0, 1.0);
		glutSetColor((int)WHITE_COLOR,   1.0, 1.0, 1.0);
	}*/

	/*void use_color(COLOR color) {
		glColor3f(
			glutGetColor((int)color, GLUT_RED),
			glutGetColor((int)color, GLUT_GREEN),
			glutGetColor((int)color, GLUT_BLUE)
		);
	}*/

	struct Color
	{
		//cell;
		positive red, green, blue;

		Color(positive _red, positive _green, positive _blue):
			red(_red), green(_green), blue(_blue)
		{}

		Color():
			red(0), green(0), blue(0)
		{}

		void use() {
			glColor3ub(red, green, blue);
		}

		void set(positive _red, positive _green, positive _blue) {
			red = _red;
			green = _green;
			blue = _blue;
		}
	};

}

#endif
