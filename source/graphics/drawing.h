#ifndef DRAWING_H
#define DRAWING_H 1

namespace graphics {

	void square() {
		glPushMatrix();
			glTranslatef(0.5, 0.5, 0);
			//glScalef(FIGURE_SIZE, FIGURE_SIZE, 0);
			glRectf(-0.5, -0.5, 0.5, 0.5);
		glPopMatrix();
	}

	void ngon(int angles = 5, int step_over = 1) {
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
			//glScalef(FIGURE_SIZE, FIGURE_SIZE, 0);
			glRotatef(90, 0, 0, 1);
			for(int j = 0; j < loops_count; j++) {
				if(use_splitter) {
					glBegin(GL_TRIANGLE_FAN);
					glVertex2f(0, 0);
				} else {
					glBegin(GL_POLYGON);
				}
				for(int i = 0; i <= loop_length; i++) {
					float deg_in_rad = (j * angle + i * step) * DEG2RAD;
					glVertex2f(cos(deg_in_rad) * radius, sin(deg_in_rad) * radius);
				}
				glEnd();
			}
		glPopMatrix();
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
