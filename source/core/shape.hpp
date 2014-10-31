#pragma once

#include "opengl.hpp"
#include "color.hpp"
#include <string>

struct PolymorphicShape;
extern PolymorphicShape default_shape;

struct Shape {

	GLuint base;

	Shape();
	~Shape();

	void display();
};

struct Block : Shape {
	Block();
};

struct Circle : Shape {
	Circle();
};

struct NGon : Shape {
	int angles, step_over;
	NGon(int _angles = 6, int _step_over = 1);
};

struct Star : NGon {
	Star();
};

struct David : NGon {
	David();
};

struct PolymorphicShape {

	Shape * shape;

	PolymorphicShape();
	PolymorphicShape(Shape * _shape);
	~PolymorphicShape();

	void set(Shape * _shape);
	void load(const std::string & shape_name);
	void display();

};
