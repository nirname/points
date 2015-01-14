#include "opengl.hpp"
#include "shape.hpp"
#include "drawing.hpp"

#include "convert.hpp"

#include <iostream>

PolymorphicShape default_shape;

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

PolymorphicShape::PolymorphicShape() {
	shape = NULL;
}

PolymorphicShape::~PolymorphicShape() {
	if(shape != NULL) {
		delete shape;
	}
}

void PolymorphicShape::load(const YAML::Node & shape_options) {
	std::cout << "Shape: " << std::ends;
	if(shape != NULL) {
		delete shape;
		shape = NULL;
	}
	if(shape == NULL) {
		try {
			shape = shape_options.as<Shape *>();
		} catch(YAML::TypedBadConversion<Shape *> & exception) {
			std::cout << "wrong value" << std::endl;
			return;
		}
	}
	if(shape != NULL && shape->base != 0) {
		std::cout << "ok" << std::ends;
	} else {
		std::cout << "shape wasn't created" << std::ends;
	}
	std::cout << std::endl;
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
