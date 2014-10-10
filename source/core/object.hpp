#pragma once

#include "point.hpp"
#include "object_kind.hpp"

struct Object {

	ObjectKind * kind;

	Object();
	~Object();

	void draw_shape() const;
	void use_color() const;

	void display(const PointSet & point_set) const;
	void display(const Point & _point) const;

};
