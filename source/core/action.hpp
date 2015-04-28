#pragma once

#include "point.hpp"
#include "object.hpp"
#include "field.hpp"

void move(Field * field, Object * object, int x, int y);
void go_to(Field * field, Object * object, int x, int y);
void rotate(Field * field, Object * object, int x, int y);

void move(Field * field, Object * object, const Point & point);
void go_to(Field * field, Object * object, const Point & point);
void rotate(Field * field, Object * object, const Point & point);
