#pragma once

#include "opengl.hpp"
#include <iostream>

struct BasicShape {

	GLuint base;

	BasicShape();
	~BasicShape();

	void display();

};

std::ostream & operator << (std::ostream & _ostream, const BasicShape & basic_shape);
