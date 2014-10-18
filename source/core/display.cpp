#include "display.hpp"

#include "library.hpp"
#include "variables.hpp"

#include "opengl.hpp"
#include "color.hpp"
#include "options.hpp"

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushAttrib(GL_CURRENT_BIT);
		glColor3ub(WHITE);
		glRectf(0.0, 0.0, screen.width, screen.height);
	glPopAttrib();
	glColor3ub(BLACK);

	// grid at screen
	/*glPushAttrib(GL_CURRENT_BIT);
		glColor3ub(GRAY);
		grid(screen.bound());
		glColor3ub(BLACK);
		grid(screen.bound(), 6);
	glPopAttrib();*/

	switch(application.mode) {
		case FOREWORD_MODE: write(std::string("Foreword")); foreword.display(); break;
		case MENU_MODE: interface.display(); break;
		case GAMEPLAY_MODE: game.display(); break;
		case SCREENSAVER_MODE: screensaver.display(); break;
		default: {
			//write(to_string(application.mode));
			break;
		}
	}

	glFlush();
	glutSwapBuffers();

}

void redisplay(int timer) {
	//clock_t time = clock();
	glutPostRedisplay();
	//time = clock() - time;
	//int frame_duration = ((float)time)/CLOCKS_PER_SEC;
	//max(1000.0 / min_fps, frame_duration);
	// ((float)time)/CLOCKS_PER_SEC
	//std::cout << "time: " << clock() << ", rest: " << graphics::sleep - time << std::endl;
	//glutTimerFunc(frame_duration, redisplay, 0);
	glutTimerFunc(50, redisplay, 0);
}

void reshape(int width, int length) {
	glOrtho(0.0, screen.width, 0.0, screen.height, -1.0, 1.0);
	glViewport(0,0,(GLsizei)width, (GLsizei)length);

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

void idle() {} // idle
