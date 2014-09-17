#pragma once

namespace graphics {

	struct Screen {

		float width, height;

		Screen(float _width, float _height);

		void initialize();
		void set(float, float);
		void adjust();

	};

	Screen::Screen(float _width, float _height):
		width(_width), height(_height)
	{}

	void Screen::initialize() {
		graphics::coordinates(0, width, 0, height);
		graphics::reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}

	void Screen::set(float _width, float _height) {
		width = _width;
		height = _height;
		initialize();
		std::cout << "Screen is switched to " << width << ":" << height << std::endl;
	}

	void Screen::adjust() {
		set(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}

}
