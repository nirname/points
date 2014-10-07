#include "action.hpp"

void move(int x, int y) {}
void go_to(int x, int y) {}
void turn(int x, int y) {}
void reflect(int x, int y) {}
void step(int x, int y) {}

void move(const Point & point) {
	move(point.column, point.row);
}

void go_to(const Point & point) {
	go_to(point.column, point.row);
}

void turn(const Point & point) {
	turn(point.column, point.row);
}

void reflect(const Point & point) {
	reflect(point.column, point.row);
}

void step(const Point & point) {
	step(point.column, point.row);
}

void reverse() {};
