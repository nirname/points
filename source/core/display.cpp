#include "display.hpp"

#include "library.hpp"
#include "variables.hpp"

#include "opengl.hpp"
#include "color.hpp"
#include "drawing.hpp"
#include "shape.hpp"
#include "math.h"
#include "options.hpp"

#include "emitter.hpp"

float fps() {
	return 0.0;
}

void display() {

	// 1. call animations
	// 2. set camera and so on
	// 3. draw scene

	int elapsed_time = glutGet(GLUT_ELAPSED_TIME);

	/*float delay = 1000.0 / options::max_fps - elapsed_time;
	if(delay < 0) {
		delay = 0;
	}
	std::cout << delay << std::endl;
	glutTimerFunc((int)ceil(delay), redisplay, 0);*/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*glPushAttrib(GL_CURRENT_BIT);
		glColor3ub(WHITE);
		glRectf(0.0, 0.0, screen.width, screen.height);
	glPopAttrib();*/

	glPushAttrib(GL_CURRENT_BIT);
		glColor3ub(BLACK);
		//base_color.use();

		// grid at screen
		/*glPushAttrib(GL_CURRENT_BIT);
			glColor3ub(GRAY);
			grid(screen.bound());
			glColor3ub(BLACK);
			grid(screen.bound(), 6);
		glPopAttrib();*/

		/*LOADING_MODE,
		FOREWORD_MODE,
		MENU_MODE,
		SCREENSAVER_MODE,
		COUNTDOWN_MODE,
		GAMEPLAY_MODE,
		INFORMATION_MODE,
		AFTERWORD_MODE*/
		switch(application.mode) {
			case LOADING_MODE: draw_text("loading"); break;
			case FOREWORD_MODE: foreword.display(); break;
			case MENU_MODE: interface.display(); break;
			case SCREENSAVER_MODE: screensaver.display(); break;
			//case COUNTDOWN_MODE: break;
			case GAMEPLAY_MODE: game.display(); break;
			//case INFORMATION_MODE: break;
			//case AFTERWORD_MODE: break;
			default: {
				draw_text(to_string(application.mode));
				break;
			}
		}

		//write(std::string("FPS"), 0, 0);

		elapsed_time = glutGet(GLUT_ELAPSED_TIME) - elapsed_time;
		//std::cout << elapsed_time << std::endl;

	glPopAttrib();

	glFlush();
	glutSwapBuffers();

}

void redisplay(int timer) {
	glutPostRedisplay();
	glutTimerFunc(50, redisplay, 0);
}

void reshape(int width, int length) {
	/*glOrtho(0.0, screen.width, 0.0, screen.height, -1.0, 1.0);
	glViewport(0, 0, (GLsizei)width, (GLsizei)length);*/

	float x_ort = width / screen.width;
	float y_ort = length / screen.height;

	if(options::smooth_zooming == false) {
		x_ort = floor(x_ort);
		y_ort = floor(y_ort);
	}

	if(options::proportional == true) {
		float ort = (x_ort < y_ort) ? x_ort : y_ort;
		x_ort = ort;
		y_ort = ort;
	}

	options::window_width = x_ort * screen.width;
	options::window_height = y_ort * screen.height;

	glViewport(
		(GLint)((width - options::window_width) / 2.0),
		(GLint)((length - options::window_height) / 2.0),
		(GLsizei)(options::window_width),
		(GLsizei)(options::window_height)
	);
} // reshape

void idle() {
	//glutPostRedisplay();
} // idle
