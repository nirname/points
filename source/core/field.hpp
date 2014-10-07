#pragma once

/*enum DIMENSION_TYPE {
	FINITE_DIMENSION,
	CLOSED_DIMENSION,// ?
	INFINITE_DIMENSION
};*/

#include "point.hpp"
#include "size.hpp"
#include "bound.hpp"

#include "data.hpp"

struct Field {

	Size size;
	Data data;
	//std::set<Point> cells;

	Field(int _width = 1, int _height = 1);
	~Field();

	Bound bound();

};
