#include "drawing.hpp"
#include "variables.hpp"
#include "options.hpp"
#include "graphics.hpp"
//#include "font.hpp"
#include <string>

DrawingFunction default_shape = square;

///Write string
//
/* Fonts:
*
* GLUT_BITMAP_8_BY_13
* GLUT_BITMAP_9_BY_15
* GLUT_BITMAP_TIMES_ROMAN_10
* GLUT_BITMAP_TIMES_ROMAN_24
* GLUT_BITMAP_HELVETICA_10
* GLUT_BITMAP_HELVETICA_12
* GLUT_BITMAP_HELVETICA_18
*/
void write(std::string string, int x, int y, void * font) {
	coordinates(0, options::window_width, 0, options::window_height);
	glRasterPos2f(x, options::window_height - y - glutBitmapHeight(font));
	for(std::string::iterator i = string.begin(); i != string.end(); ++i) {
		glutBitmapCharacter(font, *i);
	}
	coordinates(0, screen.width, 0, screen.height);
}

void write(std::string text, int x, int y, Font * _font) {
	GLuint base = _font->base;
	GLuint offset = 0;
	GLuint symbol_code;
	glPushMatrix();
		glTranslatef(-6, 0, 0);
		for(std::string::iterator i = text.begin(); i != text.end(); ++i) {
			glTranslatef(6, 0, 0);
			symbol_code = (GLuint)(*i);
			// TODO: calculate offest from charset
			if((GLuint)'A' <= symbol_code && symbol_code <= (GLuint)'Z') {
				offset = (GLuint)'A';
			} else if((GLuint)'a' <= symbol_code && symbol_code <= (GLuint)'z') {
				offset = (GLuint)'a';
			}
			glCallList(base - offset + symbol_code);
		}
	glPopMatrix();
}

/// Square
//
void square() {
	glPushMatrix();
		glTranslatef(0.5, 0.5, 0);
		glScalef(options::figure_size, options::figure_size, 0);
		glRectf(-0.5, -0.5, 0.5, 0.5);
	glPopMatrix();
}

/// Small square
//
void point() {
	glPushMatrix();
		glTranslatef(0.5, 0.5, 0);
		glScalef(options::figure_size * 0.25, options::figure_size * 0.25, 0);
		glRectf(-0.5, -0.5, 0.5, 0.5);
	glPopMatrix();
}

/// Draw n-gon
//
/// ngon(360, 1) will be equal to circle
void ngon(int angles, int step_over) {
	const float radius = 0.5;
	float angle = 360.0 / angles;
	float step = angle * step_over;
	int loop_length = angles;
	int loops_count = 1;
	bool use_splitter = ((angles % step_over) != 0);
	if(!use_splitter) {
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

/// Draw a cricle
//
void circle() {
	//if(glIsList((GLuint)CIRCLE_DISPLAY_LIST)) {
	//	glCallList((GLuint)CIRCLE_DISPLAY_LIST);
	//} else {
	glNewList((GLuint)CIRCLE_DISPLAY_LIST, GL_COMPILE_AND_EXECUTE);
	const float radius = 0.5;
	glPushMatrix();
		glTranslatef(0.5, 0.5, 0);
		glScalef(options::figure_size, options::figure_size, 0);
		glBegin(GL_POLYGON);
			float radian = 0.0f;
			for(int i = 0; i < 360; i+=2, radian += DEG2RAD*2) {
				glVertex2f(cos(radian) * radius, sin(radian) * radius);
			}
		glEnd();
	glPopMatrix();
	glEndList();
	//}
}

void star() {
	ngon(5, 2);
}

void david() {
	ngon(6, 2);
}

void line(int x1, int y1, int x2, int y2) {
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
}

//glPushAttrib(GL_ENABLE_BIT);
//glLineStipple(1, 0xAAAA);
//if(x % 10 != 0) glEnable(GL_LINE_STIPPLE);
//glDisable(GL_LINE_STIPPLE);
void grid(const Bound & bound, int _step) {
	if(bound.initial.row < bound.final.row) {
		for(int x = bound.initial.column; x <= bound.final.column; x += _step) {
			line(x, bound.initial.row, x, bound.final.row);
		}
	}
	if(bound.initial.column < bound.final.column) {
		for(int y = bound.initial.row; y <= bound.final.row; y += _step) {
			line(bound.initial.column, y, bound.final.column, y);
		}
	}
}

void display_at(void (* displayer)(), int x, int y) {
	glPushMatrix();
		glTranslatef(x, y, 0);
		displayer();
	glPopMatrix();
}

/*void emptiness(void (*draw)()){
	draw();
	glPushMatrix();
		glTranslatef((1.0 - EMPTY_SIZE) / 2, (1.0 - EMPTY_SIZE) / 2, 0);
		glScalef(EMPTY_SIZE, EMPTY_SIZE, 0);
		glPushAttrib(GL_CURRENT_BIT);
			glColor3ub(WHITE);
			draw();
		glPopAttrib();
	glPopMatrix();
}*/
