#ifndef PICTURE_H
#define PICTURE_H 1

namespace picture {

	void display();
	void reshape(int, int);
	void idle();

	void manySquares(int r, int c)
	{
		//glPushMatrix();
		for(int y=0;y<r;y++)
		{
			glPushMatrix();
			glTranslatef(0, 1*y, 0);
			for(int x=0; x<c; x++)
			{
				glPushMatrix();
				glTranslatef(1*x,0,0);
				graphics::square();
				glPopMatrix();
			}
			glPopMatrix();
		}

	}

	void draw_at(int row, int column, void(*display)())
	{
		glPushMatrix();
		glTranslatef(column, row, 0);
		display();
		glPopMatrix();
	}

	/*void qq(int x, int y)
	{
		glPushMatrix();
		glTranslatef(1*x, 1*y, 0);
		glBegin(GL_POLYGON);
		glVertex2f(0.05f, 0.05f);
		glVertex2f(0.05f, 0.95f);
		glVertex2f(0.95f, 0.95f);
		glVertex2f(0.95f, 0.05f);
		glEnd();
		glPopMatrix();
	}*/

	void display()
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		//glScalef(1, 1, 0);
		//glTranslatef(1, 1, 0);
		//glScalef(scale, scale, 0);
		//glTranslatef(offset_x, offset_y, 0);

		//glColor3ub(WHITE);
		//manySquares(100, 120);

		//glColor3ub(VIOLET); // violet
		//manySquares(7, 7);
		glColor3ub(BLUE);
		draw_at(0, 0, graphics::square);

		//graphics::circle(10);
		//graphics::Circle c; // = new engine::Circle;
		//graphics::square();
		//c.display();

		//glColor3ub(VIOLET);
		glColor3ub(WHITE);
		//engine::Square s(new graphics::Color(VIOLET));
		//s.display();

		engine::Field field(5, 5);
		field.display();

		glPopMatrix();

		glFlush();
		glutSwapBuffers();
	}

	void redisplay(int timer)
	{
		glutPostRedisplay();
		glutTimerFunc(10, picture::redisplay, 0);
	}

	void reshape(int width, int length)
	{
		glOrtho(0.0, f_width, 0.0, f_length, -1.0, 1.0);

		//glViewport(0,0,(GLsizei)width - 100, (GLsizei)length);
		//float side = (width < length) ? width : length;

		float side = (width / f_width < length / f_length) ? width / f_width : length / f_length;

		glViewport((GLint)((width - side * f_width) / 2.0), (GLint)((length - side * f_length) / 2.0), (GLsizei)(side * f_width), (GLsizei)(side * f_length));

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, f_width, 0.0, f_length, -1.0, 1.0);

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
