#ifndef DRAWING_H
#define DRAWING_H 1

namespace graphics {

	void square() {
		glPushMatrix();
			glTranslatef(0.5, 0.5, 0);
			glScalef(FIGURE_SIZE, FIGURE_SIZE, 0);
			glBegin(GL_POLYGON);
			//glColor3ub(BLUE);
			glVertex2f( 0.5,  0.5);
			//glColor3ub(GREEN);
			glVertex2f(-0.5,  0.5);
			//glColor3ub(YELLOW);
			glVertex2f(-0.5, -0.5);
			//glColor3ub(VIOLET);
			glVertex2f( 0.5, -0.5);
			glEnd();
			//glColor3ub(BLACK);
		glPopMatrix();
	}

	void ngon(int angles = 5, int step_over = 1) {
		//float radius = FIGURE_SIZE / 2;
		const float radius = 0.5;
		float angle = 360.0 / angles;
		float step = angle * step_over;
		int loop_length = angles;
		int loops_count = 1;
		bool use_splitter = ((angles % step_over) != 0);
		if(!use_splitter)
		{
			loop_length = angles / step_over;
			loops_count = step_over;
		}

		glPushMatrix();
		glTranslatef(0.5, 0.5, 0);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, 0);
		glRotatef(90, 0, 0, 1);
		//glLineWidth(2);
		for(int j = 0; j < loops_count; j++) {
			if(use_splitter) {
				glBegin(GL_TRIANGLE_FAN);
				//glColor3ub(YELLOW);
				glVertex2f(0, 0);
			} else {
				glBegin(GL_POLYGON);
			}
			//glBegin(GL_LINE_LOOP);
			//glBegin(GL_POLYGON);
			//glBegin(GL_TRIANGLES);
			//glBegin(GL_TRIANGLE_STRIP);loop_length
			for(int i = 0; i <= loop_length; i++) {
				float deg_in_rad = (j * angle + i * step) * DEG2RAD;
				/*if(i % 2 == 0) {
					glColor3ub(BLUE);
				} else {
					glColor3ub(GREEN);
				}*/
				//glColor3ub(BLUE);
				glVertex2f(cos(deg_in_rad) * radius, sin(deg_in_rad) * radius);
				/*if(use_splitter && i > 0) {
					glVertex2f(0, 0);
					glVertex2f(cos(deg_in_rad) * radius, sin(deg_in_rad) * radius);
				}*/
			}
			glEnd();
			//glColor3ub(BLACK);
		}
		glPopMatrix();
		glColor3ub(BLACK);
	}

	void circle() {
		ngon(360);
	}

	void star() {
		ngon(5, 2);
	}

	void david() {
		ngon(6, 2);
	}


}

#endif
