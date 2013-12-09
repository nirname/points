#ifndef IMAGE_H
#define IMAGE_H 1

namespace image {

	void display();
	void reshape(int, int);
	void idle();

	/*void glEnter2D(void) {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, screen.width, 0, screen.height);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);
	}

	void glLeave2D(void) {
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		glEnable(GL_DEPTH_TEST);
	}*/

	void glWrite(char text[256], int kls) {
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

		if(program.mode == TITRES_MODE) {

			//load_bmp();
			//readBMP();

			glWrite((char*)"Titres", 6);
		} else if(program.mode == MENU_MODE) {
			menu.display();
		} else if(program.mode == SCREENSAVER_MODE) {
			glWrite((char*)"Screensaver", 11);
		} else if(program.mode == GAMEPLAY_MODE) {
			game.display();
			glWrite((char*)"Gameplay", 4);
		}

		glFlush();
		glutSwapBuffers();

	}

	void redisplay(int timer)
	{
		/*if(!game.paused) {
			clock_t time = clock();
			glutPostRedisplay();
			time = clock() - time;
			//std::cout << "time: " << clock() << ", rest: " << graphics::sleep - time << std::endl;
			glutTimerFunc(graphics::sleep, redisplay, 0);
		}*/
		glutPostRedisplay();
		glutTimerFunc(graphics::sleep, redisplay, 0);
	}

	void reshape(int width, int length)
	{
		//glOrtho(0.0, screen.width, 0.0, screen.height, -1.0, 1.0);

		//glViewport(0,0,(GLsizei)width, (GLsizei)length);
		//float side = (width < length) ? width : length;
		//float margin = 50.0;
		//float padding = 10.0;

		float x_ort = width / screen.width;
		float y_ort = length / screen.height;
		float side = (x_ort < y_ort) ? x_ort : y_ort;

		glViewport(
			(GLint)((width - side * screen.width) / 2.0),
			(GLint)((length - side * screen.height) / 2.0),
			(GLsizei)(side * screen.width),
			(GLsizei)(side * screen.height)
		);

		//glMatrixMode(BASE_MATRIX_MODE);
		//glLoadIdentity();
		//glOrtho(0.0, screen.width, 0.0, screen.height, -1.0, 1.0);

		//glViewport(0, 0, 1, 1);
	}

	void idle()
	{
	//	glClear(GL_COLOR_BUFFER_BIT);
	//	glutSwapBuffers();

//		Draw();
	} // idle


}

#endif
