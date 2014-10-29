#pragma once

#include "opengl.hpp"
#include "color.hpp"

/*struct Shape;
struct Square;
struct Circle;
struct NGon;
struct David;
struct Star;*/

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
