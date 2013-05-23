#ifndef IMAGE_H
#define IMAGE_H 1

namespace image {

	void display();
	void reshape(int, int);
	void idle();

	void display()
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		glColor3ub(WHITE);

		for(engine::ViewMap::iterator view = game.views.begin(); view != game.views.end(); ++view) {
			view->second->display();
		}

		glPopMatrix();

		glFlush();
		glutSwapBuffers();
	}

	void redisplay(int timer)
	{
		glutPostRedisplay();
		glutTimerFunc(10, redisplay, 0);
	}

	void reshape(int width, int length)
	{
		glOrtho(0.0, screen.width, 0.0, screen.height, -1.0, 1.0);

		//glViewport(0,0,(GLsizei)width - 100, (GLsizei)length);
		//float side = (width < length) ? width : length;

		float x_ort = width / screen.width;
		float y_ort = length / screen.height;
		float side = (x_ort < y_ort) ? x_ort : y_ort;

		glViewport(
			(GLint)((width - side * screen.width) / 2.0),
			(GLint)((length - side * screen.height) / 2.0),
			(GLsizei)(side * screen.width),
			(GLsizei)(side * screen.height)
		);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, screen.width, 0.0, screen.height, -1.0, 1.0);

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
