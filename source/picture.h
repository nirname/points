#ifndef PICTURE_H
#define PICTURE_H 1

namespace pic {
	
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
				sgl::square();
				glPopMatrix();
			}
			glPopMatrix();
		}
		
	}
	
	void draw_at(int row, int column, void(*display)())
	{
		glPushMatrix();
		glTranslatef(1*column, 1*row, 0);
		display();
		glPopMatrix();
	}
	
	void qq(int x, int y)
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
	}
	
	void display()
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glPushMatrix();
		glScalef(scale, scale, 0);
		glTranslatef(offset_x, offset_y, 0);
		
		glColor3ub(GRAY);
		manySquares(100, 120);
		glColor3ub(VIOLET); // violet
		
		manySquares(7, 7);
				
		glColor3ub(BLUE);
		draw_at(1, 3, sgl::square);
		
		glPopMatrix();
		
		glFlush();
		glutSwapBuffers();
	}
	
	void redisplay(int timer)
	{
		glutPostRedisplay();
		glutTimerFunc(10, pic::redisplay, 0);
	}
	
	void reshape(int width, int length)
	{
		//glViewport(0,0,(GLsizei)width - 100, (GLsizei)length);
		//float side = (width < length) ? width : length;
		float side = (width / f_width < length / f_length) ? width / f_width : length / f_length;
		
		glViewport((GLint)((width - side*f_width) / 2.0), (GLint)((length - side*f_length) / 2.0), (GLsizei)(side*f_width), (GLsizei)(side*f_length));
		
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

