#pragma once

#include "point.hpp"

enum ACTION_KIND {
	/// Nothing to do
	NO_ACTION,
	/// Move an object at a given distance. Relative value
	MOVE_ACTION,
	/// Move an object to a given point
	GO_TO_ACTION,
	/// Rotate an object or change a direction (for instance, snake direction)
	TURN_ACTION,
	/// Flip an object along specified axies
	REFLECT_ACTION,
	/// Move tail of an object to head
	STEP_ACTION,
	/// Swap tail and head of object
	REVERSE_ACTION
};

void move(int x, int y);
void go_to(int x, int y);
void turn(int x, int y);
void reflect(int x, int y);
void step(int x, int y);

void move(const Point & point);
void go_to(const Point & point);
void turn(const Point & point);
void reflect(const Point & point);
void step(const Point & point);

void reverse();
