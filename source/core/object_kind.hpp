#pragma once

#include "shape.hpp"
#include "color.hpp"

#include <cstddef>

struct ObjectKind {

	Shape * shape;
	Color * color;

	ObjectKind();

	void draw_shape();
	void use_color();

};
