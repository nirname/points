#pragma once

#include "opengl.hpp"
#include "color.hpp"
#include <string>

#include "basic_shape.hpp"

struct Block : BasicShape {
	Block();
};

struct Circle : BasicShape {
	Circle();
};

struct Queen : BasicShape {
	Queen();
};

struct NGon : BasicShape {
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

struct Shape {

	BasicShape * basic_shape;

	Shape();
	Shape(BasicShape * basic_shape);
	~Shape();

	void clear();
	void display();

};

extern Shape default_shape;
