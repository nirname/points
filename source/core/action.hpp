#pragma once

#include "point.hpp"

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
