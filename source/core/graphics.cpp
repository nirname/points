#include "graphics.hpp"

/// Set coordinate grid
//
void coordinates(GLdouble left, GLdouble right, GLdouble  bottom, GLdouble top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/// Set coordinate grid
//
void coordinates(GLdouble right, GLdouble top) {
	coordinates(0, right, 0, top);
}
