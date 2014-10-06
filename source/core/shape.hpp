#pragma once

#include "color.hpp"

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

/*struct Retro : Shape {
	~Retro();
	void display();
};*/

/*struct Ring : Shape {
	~Ring();
	void display();
};*/

/*struct EmptySquare : Shape {
	~EmptySquare();
	void display();
};*/
