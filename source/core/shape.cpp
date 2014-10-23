#include "shape.hpp"
#include "drawing.hpp"

//const float EMPTY_SIZE = 0.6f;

ShapeFunction default_shape = square;

Shape::~Shape() {}

Square::~Square() {}

void Square::display() {
	square();
}

Circle::~Circle() {}

void Circle::display() {
	circle();
}

NGon::~NGon() {}

NGon::NGon(int _angles, int _step_over) {
	angles = _angles;
	step_over = _step_over;
}

void NGon::display() {
	ngon(angles, step_over);
}

David::~David() {}

void David::display() {
	david();
}

Star::~Star() {}

void Star::display() {
	star();
}
