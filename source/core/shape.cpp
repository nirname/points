#include "shape.hpp"
#include "drawing.hpp"

Shape::~Shape() {}

Square::~Square() {}

void Square::display() {
	square();
}

Circle::~Circle() {}

void Circle::display() {
	circle();
}

NGon::~NGon() {}

NGon::NGon(int _angles, int _step_over) {
	angles = _angles;
	step_over = _step_over;
}

void NGon::display() {
	ngon(angles, step_over);
}

David::~David() {}

void David::display() {
	david();
}

Star::~Star() {}

void Star::display() {
	star();
}

/*void EmptySquare::display() {
	square();
	glPushMatrix();
		glTranslatef((1.0 - EMPTY_SIZE) / 2, (1.0 - EMPTY_SIZE) / 2, 0);
		glScalef(EMPTY_SIZE, EMPTY_SIZE, 0);
		glPushAttrib(GL_CURRENT_BIT);
			glColor3ub(WHITE);
			square();
		glPopAttrib();
	glPopMatrix();
}*/


/*void Ring::display() {
	circle();
	glPushMatrix();
		glTranslatef((1.0 - EMPTY_SIZE) / 2, (1.0 - EMPTY_SIZE) / 2, 0);
		glScalef(EMPTY_SIZE, EMPTY_SIZE, 0);
		glPushAttrib(GL_CURRENT_BIT);
			glColor3ub(WHITE);
			circle();
		glPopAttrib();
	glPopMatrix();
}*/

/*void Retro::display() {
	square();
	glPushMatrix();
		glTranslatef((1.0 - EMPTY_SIZE) / 2, (1.0 - EMPTY_SIZE) / 2, 0);
		glScalef(EMPTY_SIZE, EMPTY_SIZE, 0);
		glPushAttrib(GL_CURRENT_BIT);
			glColor3ub(WHITE);
			square();
		glPopAttrib();
		glPushMatrix();
			glTranslatef((1.0 - EMPTY_SIZE) / 2, (1.0 - EMPTY_SIZE) / 2, 0);
			glScalef(EMPTY_SIZE, EMPTY_SIZE, 0);
			square();
		glPopMatrix();
	glPopMatrix();
}*/
