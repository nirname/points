#pragma once

// TODO: remove this class, make global variables instead
namespace graphics {

	struct Screen {

		float width, height; //, margin
		Screen(float _width, float _height = SMALL_ASPECT):
			width(_width), height(_height)
		{}

		void initialize();
		void set(float, float);
		void adjust();

	};

	void Screen::initialize() {
		graphics::coordinates(0, width, 0, height);
		graphics::reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}

	void Screen::set(float _width, float _height) {
		width = _width;
		height = _height;
		std::cout << "Screen switched to " << width << ":" << height << std::endl;
		initialize();
	}
	
	void Screen::adjust() {
		set(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}

}
