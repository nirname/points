#pragma once

namespace graphics {

	void gl_write();
	void display();
	void reshape(int, int);
	void idle();

}

namespace graphics {

	void gl_write(char text[256], int kls) {
		glRasterPos2f(screen.width / 10, screen.height / 10);
		for (int i = 0; i < kls; i++) {
			glutBitmapCharacter((int*)GLUT_BITMAP_8_BY_13, (int)text[i]);
		}
	}

	void display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPushAttrib(GL_CURRENT_BIT);
			glColor3ub(WHITE);
			glRectf(0.0, 0.0, screen.width, screen.height);
		glPopAttrib();
		glColor3ub(BLACK);

		

		if(application.mode == FOREWORD_MODE) {

			// TODO: skip if there is nothing to show
			//opening.display();
			gl_write((char *)"Titres", 6);
		} else if(application.mode == LOADING_MODE) {
			gl_write((char *)"Loading", 7);
		} else if(application.mode == MENU_MODE) {
			menu.display();
			glPushAttrib(GL_CURRENT_BIT);
				glColor3ub(GRAY);
				grid(screen.bound());
				glColor3ub(BLACK);
				grid(screen.bound(), 6);
			glPopAttrib();
		} else if(application.mode == SCREENSAVER_MODE) {
			gl_write((char *)"Screensaver", 11);
		} else if(application.mode == GAMEPLAY_MODE) {
			game.display();
			gl_write((char *)"Gameplay", 4);
		}

		glFlush();
		glutSwapBuffers();

	}

	void redisplay(int timer)
	{
		//if(!game.paused) {
			clock_t time = clock();
			glutPostRedisplay();
			time = clock() - time;
			//std::cout << "time: " << clock() << ", rest: " << graphics::sleep - time << std::endl;
			//glutTimerFunc(graphics::sleep, redisplay, 0);
		//}
		//glutPostRedisplay();
		//glutTimerFunc(graphics::sleep, redisplay, 0);
	}

	void reshape(int width, int length)
	{
		//glOrtho(0.0, screen.width, 0.0, screen.height, -1.0, 1.0);

		//glViewport(0,0,(GLsizei)width, (GLsizei)length);
		//float side = (width < length) ? width : length;
		//float margin = 50.0;
		//float padding = 10.0;

		/*float x_ort = width / screen.width;
		float y_ort = length / screen.height;
		float side = (x_ort < y_ort) ? x_ort : y_ort;
		
		glViewport(
			(GLint)((width - side * screen.width) / 2.0),
			(GLint)((length - side * screen.height) / 2.0),
			(GLsizei)(side * screen.width),
			(GLsizei)(side * screen.height)
		);*/
		
		int x_ort = width / screen.width;
		int y_ort = length / screen.height;
		int side = (x_ort < y_ort) ? x_ort : y_ort;

		glViewport(
			(GLint)((width - side * screen.width) / 2),
			(GLint)((length - side * screen.height) / 2),
			(GLsizei)(side * screen.width),
			(GLsizei)(side * screen.height)
		);

	} // reshape

	void idle() {
	} // idle


}
