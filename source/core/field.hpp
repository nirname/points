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

#include <set>

typedef std::set<Point> CellsSet;

struct Field {

	Size size;
	Data data;
	CellsSet cells;

	Field(int _width = 1, int _height = 1);
	~Field();

	void move(Object * object, Point point);

	Bound bound();

};
