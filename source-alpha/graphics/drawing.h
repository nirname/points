#pragma once

namespace graphics {

	void (*default_shape)() = square;

	// Fonts:
	//
	// GLUT_BITMAP_8_BY_13
	// GLUT_BITMAP_9_BY_15
	// GLUT_BITMAP_TIMES_ROMAN_10
	// GLUT_BITMAP_TIMES_ROMAN_24
	// GLUT_BITMAP_HELVETICA_10
	// GLUT_BITMAP_HELVETICA_12
	// GLUT_BITMAP_HELVETICA_18
	//
	void write(std::string string, int x = 0, int y = 0, void * font = GLUT_BITMAP_9_BY_15) {
		graphics::coordinates(0, options::window_width, 0, options::window_height);
		glRasterPos2f(x, options::window_height - y - glutBitmapHeight(font));
		//glRasterPos2f(x, y);
		//glWindowPos2f(x, y - glutBitmapHeight(font));
		for(std::string::iterator i = string.begin(); i != string.end(); ++i) {
			glutBitmapCharacter(font, *i);
		}
		graphics::coordinates(0, screen.width, 0, screen.height);
	}

	/*void draw_string(std::string & string) {
		for (std::string::iterator i = string.begin(); i != string.end(); ++i) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *i);
		}
	}
	float stroke_length(std::string & string) {
		float length = 0;
		for (std::string::iterator i = string.begin(); i != string.end(); ++i) {
			length += glutStrokeWidth(GLUT_STROKE_ROMAN, *i);
		}
		return length;
	}*/

	void square() {
		glPushMatrix();
			glTranslatef(0.5, 0.5, 0);
			glScalef(options::figure_size, options::figure_size, 0);
			glRectf(-0.5, -0.5, 0.5, 0.5);
		glPopMatrix();
	}

	void point() {
		glPushMatrix();
			glTranslatef(0.5, 0.5, 0);
			glScalef(options::figure_size * 0.25, options::figure_size * 0.25, 0);
			glRectf(-0.5, -0.5, 0.5, 0.5);
			/*glBegin(GL_POINTS);
			glTranslatef(0.5, 0.5, 0);
				glPointSize(10);
				glVertex2f(0, 0);
				glPointSize(1);
			glEnd();*/
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
			glScalef(options::figure_size, options::figure_size, 0);
			glRotatef(90, 0, 0, 1);
			for(int j = 0; j < loops_count; j++) {
				if(use_splitter) {
					glBegin(GL_TRIANGLE_FAN);
					glVertex2f(0, 0);
				} else {
					glBegin(GL_POLYGON);
				}
				for(int i = 0; i <= loop_length; i++) {
					float rad = (j * angle + i * step) * DEG2RAD;
					glVertex2f(cos(rad) * radius, sin(rad) * radius);
				}
				glEnd();
			}
		glPopMatrix();
	}

	/*void circle() {
		ngon(360);
	}*/

	void circle() {
		const float radius = 0.5;
		glPushMatrix();
			glTranslatef(0.5, 0.5, 0);
			glScalef(options::figure_size, options::figure_size, 0);
			glBegin(GL_POLYGON);
				float radian = 0.0f;
				for(int i = 0; i < 360; i++, radian += DEG2RAD) {
					glVertex2f(cos(radian) * radius, sin(radian) * radius);
				}
			glEnd();
		glPopMatrix();
	}

	void star() {
		ngon(5, 2);
	}

	void david() {
		ngon(6, 2);
	}

}
