#include "basic_shape.hpp"
#include <iostream>

BasicShape::BasicShape() {
	base = glGenLists(1);
}

BasicShape::~BasicShape() {
	glDeleteLists(base, 1);
}

void BasicShape::display() {
	glCallList(base);
}

std::ostream & operator << (std::ostream & _ostream, const BasicShape & basic_shape) {
	_ostream << "BasicShape";
	return _ostream;
}
