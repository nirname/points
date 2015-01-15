#include "opengl.hpp"
#include "shape.hpp"
#include "drawing.hpp"

#include "convert_shape.hpp"

#include <iostream>

Block::Block() {
	glNewList(base, GL_COMPILE);
		draw_block();
	glEndList();
}

Circle::Circle() {
	glNewList(base, GL_COMPILE);
		draw_circle();
	glEndList();
}

Queen::Queen() {
	glNewList(base, GL_COMPILE);
		draw_queen();
	glEndList();
}

NGon::NGon(int _angles, int _step_over) {
	angles = _angles;
	step_over = _step_over;
	glNewList(base, GL_COMPILE);
		draw_ngon(angles, step_over);
	glEndList();
}

Star::Star() : NGon(5, 2) {}

David::David() : NGon(6, 2) {}

Diamond::Diamond() : NGon(4, 1) {}

Triangle::Triangle() : NGon(3, 1) {}

Shape default_shape;

Shape::Shape() {
	basic_shape = NULL;
}

Shape::~Shape() {
	clear();
}

void Shape::clear() {
	if(basic_shape != NULL) {
		delete basic_shape;
		basic_shape = NULL;
	}
};

void Shape::display() {
	if(basic_shape != NULL) {
		basic_shape->display();
	}
}
