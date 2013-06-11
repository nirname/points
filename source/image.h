#ifndef IMAGE_H
#define IMAGE_H 1

namespace image {

	void display();
	void reshape(int, int);
	void idle();

	int sleep = 1000 / 30;
	int direction = -1;

	void display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT);

		// clear screen
		glColor3ub(WHITE);
		glBegin(GL_POLYGON);
			glVertex2f(0, 0);
			glVertex2f(screen.width, 0);
			glVertex2f(screen.width, screen.height);
			glVertex2f(0, screen.height);
		glEnd();

		for (graphics::AnimationMapIterator i = game.animations.begin(); i != game.animations.end(); ++i) {
			i->second->next();
		}

			/*if(scale >= 1) {
				direction = -1;
			}
			if(scale <= 0) {
				direction = 1;
			}
			scale += direction * 0.1;*/

		glColor3ub(BLACK);
		glPushMatrix();

			for(engine::ViewMap::iterator view = game.views.begin(); view != game.views.end(); ++view) {
				view->second->display();
			}

			/*glPushMatrix();
				//glLoadIdentity();
				//glScalef(scale, scale, 0);
				//gluOrtho2D(0, 1, 0, 1);
				//game.objects[std::string("Sokoban")]->display();
				//graphics::ngon(3, 1);
				//graphics::ngon(4, 1);
				//graphics::ngon(5, 1);
				//graphics::ngon(5, 2);
				//graphics::ngon(6, 1);
				//graphics::ngon(6, 2);
				//graphics::ngon(7, 1);
				//graphics::ngon(7, 2);
				//graphics::ngon(7, 3);
				//graphics::ngon(8, 1);
				//graphics::ngon(8, 2);
				//graphics::ngon(8, 3);
				//graphics::ngon(9, 1);
				//graphics::ngon(9, 2);
				//graphics::ngon(9, 3);
				//graphics::ngon(9, 4);
				//graphics::circle();
			glPopMatrix();/**/

		glPopMatrix();

		glFlush();
		glutSwapBuffers();

	}

	void redisplay(int timer)
	{
		if(!game.paused) {
			clock_t time;
			time = clock();
			glutPostRedisplay();
			time = clock() - time;
			//std::cout << "time: " << time << ", rest: " << sleep - time << std::endl;
			glutTimerFunc(sleep, redisplay, 0);
		}
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

		//glMatrixMode(BASE_MATRIX_MODE);
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
