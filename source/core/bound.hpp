#pragma once

#include "point.hpp"

/// Describes a bound with initial and final points
//
struct Bound {

	/// Left bottom point
	Point initial;
	/// Right top point
	Point final;

	/// Create bound with inital point at (0, 0) and final point from a parameter
	Bound(const Point & _final);
	/// Create with initial and final points
	Bound(Point _initial, Point _final);
	/// Copy constructor
	Bound(const Bound & _bound);

	/// Сheck if bound contains a point
	bool contains(Point x) const;

	/// Shift initial and final points in forward direction
	Bound & operator += (const Point & x);
	/// Shift initial and final point in backward direction
	Bound & operator -= (const Point & x);

	/// Calculates intersection of bounds
	Bound & operator &= (const Bound & x);

};

// Get another shifted bound
Bound operator + (const Bound & _bound, const Point & _point);

// Get another shifted bound
Bound operator - (const Bound & _bound, const Point & _point);

// Get intersection of bounds
Bound operator & (const Bound & _a, const Bound & _b);

/*std::ostream & operator << (std::ostream & _ostream, const Bound & _bound) {
	_ostream << "Bound(" << _bound.initial << ", " << _bound.final << ")";
	return _ostream;
}*/
