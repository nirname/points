#include "graphics.hpp"

/// Set coordinate grid
//
void coordinates(GLdouble left, GLdouble right, GLdouble  bottom, GLdouble top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

/// Set coordinate grid
//
void coordinates(GLdouble right, GLdouble top) {
	coordinates(0, right, 0, top);
}
