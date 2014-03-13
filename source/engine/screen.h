#pragma once

namespace engine {

	struct Screen {

		float width, height, margin;
		Screen(float _width = 96.0, float _height = 54.0, float _margin = 0.0):
			width(_width), height(_height), margin(_margin)
		{}
		
		void load();
		void set(float, float);
		//void set(SCREEN_FORMAT);
		
		Bound bound();

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
		width = _width;
		height = _height;
		std::cout << "Screen switched to " << width << ":" << height << std::endl;
		load();
	}
	
	Bound Screen::bound() {
		return Bound(Point(width, height));
	}

}
