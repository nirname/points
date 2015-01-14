#include "basic_shape.hpp"

BasicShape::BasicShape() {
	base = glGenLists(1);
}

BasicShape::~BasicShape() {
	glDeleteLists(base, 1);
}

void BasicShape::display() {
	glCallList(base);
}
