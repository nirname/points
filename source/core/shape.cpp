#include "shape.hpp"
#include "drawing.hpp"

Shape::Shape() {
	base = glGenLists(1);
}

Shape::~Shape() {
	glDeleteLists(base, 1);
}

void Shape::display() {
	glCallList(base);
}

Block::Block() {
	glNewList(base, GL_COMPILE);
		square();
	glEndList();
}

Circle::Circle() {
	glNewList(base, GL_COMPILE);
		circle();
	glEndList();
}

NGon::NGon(int _angles, int _step_over) {
	angles = _angles;
	step_over = _step_over;
	glNewList(base, GL_COMPILE);
		ngon(angles, step_over);
	glEndList();
}

Star::Star() : NGon(5, 2) {}
David::David() : NGon(6, 2) {}
