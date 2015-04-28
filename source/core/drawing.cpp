#include "drawing.hpp"
#include <cmath>
//#include "variables.hpp"
#include "graphics.hpp"
#include "font.hpp"
#include "screen.hpp"

extern Font font;
extern Screen screen;

namespace options {
	extern int padding;
	extern int window_width;
	extern int window_height;

	float figure_size() {
		return 1.0 - 0.05 * padding * 2;
	}
}

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

/// Draw text
//
void draw_text(std::string text, Font * _font) {
	if(_font == NULL) {
		_font = &font;
	}
	GLuint base = _font->base;
	GLuint offset = 0;
	GLuint symbol_code;
	glPushMatrix();
		for(std::string::iterator i = text.begin(); i != text.end(); ++i) {
			symbol_code = (GLuint)(*i);
			// TODO: calculate offest from charset
			offset = (GLuint)'!';
			if((GLuint)'a' <= symbol_code && symbol_code <= (GLuint)'z') {
				offset = (GLuint)'A';
			} else if((GLuint)'{' <= symbol_code && symbol_code <= (GLuint)'~') {
				offset = (GLuint)'A' - 6;
			}
			if(symbol_code != (GLuint)' ') {
				glCallList(base + symbol_code - offset);
			}
			glTranslatef(_font->width + 1, 0, 0);
		}
	glPopMatrix();
}

/// Square
//
void draw_block() {
	glPushMatrix();
		glTranslatef(0.5, 0.5, 0);
		glScalef(options::figure_size(), options::figure_size(), 0);
		glRectf(-0.5, -0.5, 0.5, 0.5);
	glPopMatrix();
}

void draw_queen() {
	glPushMatrix();
		glTranslatef(0.5, 0.5, 0);
		glScalef(options::figure_size(), options::figure_size(), 1);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f( 0.0,  -0.5);
			glVertex2f(-0.3,  -0.5);
			glVertex2f(-0.5,   0.2);
			glVertex2f(-0.22, -0.05);
			glVertex2f(-0.2,   0.5);
			glVertex2f( 0.0,   0.0);
		glEnd();
		glScalef(-1, 1, 1);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f( 0.0,  -0.5);
			glVertex2f(-0.3,  -0.5);
			glVertex2f(-0.5,   0.2);
			glVertex2f(-0.22, -0.05);
			glVertex2f(-0.2,   0.5);
			glVertex2f( 0.0,   0.0);
		glEnd();
	glPopMatrix();
}

/// Draw n-gon
//
/// ngon(360, 1) will be equal to circle
void draw_ngon(int angles, int step_over) {
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
		glScalef(options::figure_size(), options::figure_size(), 0);
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
void draw_circle() {
	const float radius = 0.5;
	glPushMatrix();
		glTranslatef(0.5, 0.5, 0);
		glScalef(options::figure_size(), options::figure_size(), 0);
		glBegin(GL_POLYGON);
			float radian = 0.0f;
			for(int i = 0; i < 360; i+=4, radian += DEG2RAD*4) {
				glVertex2f(cos(radian) * radius, sin(radian) * radius);
			}
		glEnd();
	glPopMatrix();
}

void draw_line(int x1, int y1, int x2, int y2) {
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
}

//glPushAttrib(GL_ENABLE_BIT);
//glLineStipple(1, 0xAAAA);
//if(x % 10 != 0) glEnable(GL_LINE_STIPPLE);
//glDisable(GL_LINE_STIPPLE);
void draw_grid(const Bound & bound, int _step) {
	if(bound.initial.row < bound.final.row) {
		for(int x = bound.initial.column; x <= bound.final.column; x += _step) {
			draw_line(x, bound.initial.row, x, bound.final.row);
		}
	}
	if(bound.initial.column < bound.final.column) {
		for(int y = bound.initial.row; y <= bound.final.row; y += _step) {
			draw_line(bound.initial.column, y, bound.final.column, y);
		}
	}
}

void draw_border(const Size & size) {
	draw_line(0, 0, size.width, 0);
	draw_line(0, size.height, size.width, size.height);
	draw_line(0, 0, 0, size.height);
	draw_line(size.width, 0, size.width, size.height);

	//glRectf(0, 0, size.width, size.height);
}
