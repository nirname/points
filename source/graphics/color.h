#ifndef COLOR_H
#define COLOR_H 1

// simple colors
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0
#define GRAY 127, 127, 127

#define BLUE 0, 0, 255
#define YELLOW 255, 255, 0
#define GREEN 0, 255, 0
#define RED 255, 0, 0
#define VIOLET 255, 0, 255
#define AZURE 61, 222, 235
#define ORANGE 245, 121, 0

// soft colors
#define SOFT_BLUE 17, 154, 255
#define SOFT_YELLOW 255, 232, 17
#define SOFT_GREEN 28, 174, 35
#define SOFT_RED 235, 80, 80
#define SOFT_VIOLET 175, 0, 185

// light colors
#define LIGHT_GRAY 192, 192, 192

// dark colors
#define DARK_VIOLET 48, 14, 57
#define DARK_GRAY 63, 63, 63

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

		void print(std::ostream & _ostream) const {
			_ostream << "Color#" << this << " ("
				<< red << ", "
				<< green << ", "
				<< blue
			<< ")";
		}

	};

	std::ostream & operator << (std::ostream & _ostream, const Color & _color) {
		_color.print(_ostream);
		return _ostream;
	}

	void operator >> (const YAML::Node & options, Color & color) {
		if(options.IsSequence()) {
			color.red = options[0].as<positive>();
			color.green = options[1].as<positive>();
			color.blue = options[2].as<positive>();
		} else if (options.IsMap()) {
			if(options["red"]) color.red = options["red"].as<positive>();
			if(options["green"]) color.green = options["green"].as<positive>();
			if(options["blue"]) color.blue = options["blue"].as<positive>();
		} else {
			throw WRONG_YAML_TYPE;
		}
	}

}

#endif
