#pragma once

namespace engine {

	struct Screen {

		float width, height, margin;
		Screen(float _width = 10.0, float _height = 10.0, float _margin = 0.0):
			width(_width), height(_height), margin(_margin)
		{}

		void load();
		void set(float, float);

	};

	void Screen::load() {

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0, screen.width, 0.0, screen.height);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		graphics::reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}

	void Screen::set(float _width, float _height) {
		std::cout << "Screen switch" << std::endl;
		width = _width;
		height = _height;
		load();
	}

}
