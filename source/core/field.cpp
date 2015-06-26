#include "field.hpp"

Field::Field(int _width, int _height) {
	size = Size(_width, _height);
}

Field::~Field() {
	data.clear();
}

void Field::move(Object * object, Point point, Interactions & interactions) {
	data.move(object, point, interactions, bound());
}

Bound Field::bound() {
	return Bound(Point(size.width, size.height) - Point(1, 1));
}
