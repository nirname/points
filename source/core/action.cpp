#include "action.hpp"

void move(Field * field, Object * object, int x, int y) {}
void go_to(Field * field, Object * object, int x, int y) {}
void rotate(Field * field, Object * object, int x, int y) {}

void move(Field * field, Object * object, const Point & point) {
	move(field, object, point.column, point.row);
}

void go_to(Field * field, Object * object, const Point & point) {
	go_to(field, object, point.column, point.row);
}

void rotate(Field * field, Object * object, const Point & point) {
	rotate(field, object, point.column, point.row);
}
