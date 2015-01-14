#pragma once

#include "opengl.hpp"
#include "color.hpp"
#include <string>

#include "yaml.hpp"

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

struct Queen : Shape {
	Queen();
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

struct Diamond : NGon {
	Diamond();
};

struct Triangle : NGon {
	Triangle();
};

struct PolymorphicShape {

	Shape * shape;

	PolymorphicShape();
	PolymorphicShape(Shape * _shape);
	~PolymorphicShape();

	void set(Shape * _shape);
	void load(const YAML::Node & shape_options);
	void display();

};

extern PolymorphicShape default_shape;
