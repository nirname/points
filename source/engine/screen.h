#ifndef SCREEN_H
#define SCREEN_H 1

namespace engine {

	struct Screen {
		float width, height, margin;
		Screen(float _width = 10.0, float _height = 10.0, float _margin = 0.0):
			width(_width), height(_height), margin(_margin)
		{}

		void load() {

			glMatrixMode(GL_PROJECTION);
			//glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0.0, screen.width, 0.0, screen.height);

			glMatrixMode(GL_MODELVIEW);
			//glPushMatrix();
			glLoadIdentity();

			image::reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		}

		void set(float _width, float _height) {
			std::cout << "Screen switch" << std::endl;
			width = _width;
			height = _height;
			load();
		}

	};

}

#endif
