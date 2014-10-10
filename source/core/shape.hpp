#pragma once

#include "color.hpp"

extern void (*default_shape)();

struct Shape {
	virtual ~Shape() = 0;
	virtual void display() = 0;
};

struct Square : Shape {
	~Square();
	void display();
};

struct Circle : Shape {
	~Circle();
	void display();
};

struct NGon : Shape {
	~NGon();
	int angles, step_over;
	NGon(int _angles = 6, int _step_over = 1);
	void display();
};

struct David : Shape {
	~David();
	void display();
};

struct Star : Shape {
	~Star();
	void display();
};
