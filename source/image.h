#ifndef IMAGE_H
#define IMAGE_H 1

namespace image {

	void display();
	void reshape(int, int);
	void idle();

	void manySquares(int r, int c)
	{
		//glPushMatrix();
		for(int y = 0; y < r; y++)
		{
			glPushMatrix();
			glTranslatef(0, y, 0);
			for(int x = 0; x < c; x++)
			{
				glPushMatrix();
				glTranslatef(x, 0, 0);
				graphics::square();
				glPopMatrix();
			}
			glPopMatrix();
		}
	}

	void display()
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		glColor3ub(WHITE);
		
		for(engine::ViewMap::iterator view = game.views.begin(); view != game.views.end(); ++view) {
			view->second->display();
		}
		
		//glScalef(1, 1, 0);
		//glTranslatef(1, 1, 0);
		//glScalef(scale, scale, 0);
		//glTranslatef(offset_x, offset_y, 0);

		//glColor3ub(WHITE);
		//manySquares(100, 120);

		//glColor3ub(VIOLET); // violet
		//manySquares(7, 7);
		//glColor3ub(BLUE);
		//draw_at(0, 0, graphics::square);

		//draw_at(0, 2, graphics::square);
		//graphics::circle(10);
		//graphics::Circle c; // = new engine::Circle;
		//graphics::square();
		//c.display();

		//glColor3ub(VIOLET);
		//engine::Square s(new graphics::Color(VIOLET));
		//s.display();
		//engine::Field field(6, 6);
		//engine::View view(&field, engine::Point(0, 0), engine::Point(-2, 3));
		//view.size = engine::Size(5, 5);
		//view.display();

		//graphics::Circle c;

		/*glColor3ub(VIOLET);
		for(auto i = points.begin(); i != points.end(); ++i) {
			glPushMatrix();
			glTranslatef(i->second.column + 0.5, i->second.row + 0.5, 0);
			graphics::circle();
			glPopMatrix();
		}*/

		/*for(QIterator i = info.begin(); i != info.end(); ++i) {
			glPushMatrix();
			glTranslatef(i->second, i->first, 0);
			graphics::square();
			glPopMatrix();
		}*/

		//glColor3ub(GREEN);
		/*for(auto i = line.begin(); i != line.end(); ++i) {
			glPushMatrix();
			glTranslatef(0 + 0.5, *i + 0.5, 0);
			graphics::ngon(6, 2);
			glPopMatrix();
		}*/

		/*glPushMatrix();
		glTranslatef(0 + 0.5, 0 + 0.5, 0);
		graphics::ngon(5, 1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1 + 0.5, 0 + 0.5, 0);
		graphics::ngon(6, 2);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(2 + 0.5, 0 + 0.5, 0);
		graphics::ngon(8, 2);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(3 + 0.5, 0 + 0.5, 0);
		graphics::ngon(8, 3);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(4 + 0.5, 0 + 0.5, 0);
		graphics::ngon(5, 2);
		glPopMatrix();

		glPopMatrix();*/

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

		glViewport((GLint)((width - side * screen.width) / 2.0), (GLint)((length - side * screen.height) / 2.0), (GLsizei)(side * screen.width), (GLsizei)(side * screen.height));

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
