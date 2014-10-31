#include "opengl.hpp"
#include "shape.hpp"
#include "drawing.hpp"

#include <iostream>

PolymorphicShape default_shape;

Shape::Shape() {
	std::cout << "new Shape with base " << std::ends;
	base = glGenLists(1);
	std::cout << base << std::endl;
}

Shape::~Shape() {
	glDeleteLists(base, 1);
}

void Shape::display() {
	glCallList(base);
}

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

NGon::NGon(int _angles, int _step_over) {
	angles = _angles;
	step_over = _step_over;
	glNewList(base, GL_COMPILE);
		draw_ngon(angles, step_over);
	glEndList();
}

Star::Star() : NGon(5, 2) {}

David::David() : NGon(6, 2) {}

PolymorphicShape::PolymorphicShape() {
	shape = NULL;
}

PolymorphicShape::~PolymorphicShape() {
	if(shape != NULL) {
		delete shape;
	}
}

void PolymorphicShape::load(const std::string & shape_name) {
	if(shape != NULL) {
		delete shape;
		shape = NULL;
	}

	if(shape == NULL) {
		shape = new Block;
	}
}

void PolymorphicShape::set(Shape * _shape) {
	if(shape != NULL) {
		delete shape;
		shape = NULL;
	}
	shape = _shape;
};

void PolymorphicShape::display() {
	if(shape != NULL) {
		shape->display();
	}
}
