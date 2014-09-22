#pragma once

/// Describes position by specifying coordinates for each dimension
//
struct Point {

	int column;
	int row;

	Point(int _column = 0, int _row = 0);
	Point(const Point & x);

	Point & operator += (const Point & x);
	Point & operator -= (const Point & x);
	Point & operator *= (const Point & x);

	bool operator < (const Point & x) const;

};

Point operator + (const Point & a, const Point & b);
Point operator - (const Point & a, const Point & b);
Point operator * (const Point & a, const Point & b);

Point min(Point a, Point b);
Point max(Point a, Point b);
