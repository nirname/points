#pragma once

#include "point.hpp"
#include "object_kind.hpp"

struct Object {

	ObjectKind * kind;
	//ObjectPoints mask; // TODO: move mask to object kind

	Object();
	~Object();

	void initialize();

	void draw_shape();
	void use_color();

	//void display(const ObjectPoints & _points);
	void display(const Point & _point);

};
