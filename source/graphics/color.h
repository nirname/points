#ifndef COLOR_H
#define COLOR_H 1

// simple colors
#define WHITE 255, 255, 255
#define GRAY 127, 127, 127
#define BLACK 0, 0, 0

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

	struct Color
	{
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
		try {
			Color buffer;
			if(options.IsSequence()) {
				buffer.red = options[0].as<positive>();
				buffer.green = options[1].as<positive>();
				buffer.blue = options[2].as<positive>();
			} else if (options.IsMap()) {
				if(options["red"]) { buffer.red = options["red"].as<positive>(); }
				if(options["green"]) { buffer.green = options["green"].as<positive>(); }
				if(options["blue"]) { buffer.blue = options["blue"].as<positive>(); }
			} else if (options.IsScalar()) {
				std::string color_name = options.as<std::string>();
				if ( color_name == "BLACK" ) color.set( BLACK );
				else if ( color_name == "WHITE" ) color.set( WHITE );
				else if ( color_name == "GRAY" ) color.set( GRAY );
				else if ( color_name == "BLUE" ) color.set( BLUE );
				else if ( color_name == "YELLOW" ) color.set( YELLOW );
				else if ( color_name == "GREEN" ) color.set( GREEN );
				else if ( color_name == "RED" ) color.set( RED );
				else if ( color_name == "VIOLET" ) color.set( VIOLET );
				else if ( color_name == "AZURE" ) color.set( AZURE );
				else if ( color_name == "ORANGE" ) color.set( ORANGE );
				else if ( color_name == "SOFT_BLUE" ) color.set( SOFT_BLUE );
				else if ( color_name == "SOFT_YELLOW" ) color.set( SOFT_YELLOW );
				else if ( color_name == "SOFT_GREEN" ) color.set( SOFT_GREEN );
				else if ( color_name == "SOFT_RED" ) color.set( SOFT_RED );
				else if ( color_name == "SOFT_VIOLET" ) color.set( SOFT_VIOLET );
				else if ( color_name == "LIGHT_GRAY" ) color.set( LIGHT_GRAY );
				else if ( color_name == "DARK_VIOLET" ) color.set( DARK_VIOLET );
				else if ( color_name == "DARK_GRAY" ) color.set( DARK_GRAY );
			}
			color = buffer;
		} catch(...) {
		}
	}

}

#endif
