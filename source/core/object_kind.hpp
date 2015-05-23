#pragma once

#include <cstddef>

#include "shape.hpp"
#include "color.hpp"
#include "point_set.hpp"

struct ObjectKind {

	Shape * shape;
	Color * color;

	PointSet mask;

	ObjectKind();

	void draw_shape();
	void use_color();

};
