#pragma once

namespace engine {

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

	Bound::Bound(const Point & _final):
		initial(Point(0, 0)), final(_final)
	{}

	Bound::Bound(Point _initial, Point _final):
		initial(_initial), final(_final)
	{ /* do not normilize here*/ }

	Bound::Bound(const Bound & _bound):
		initial(_bound.initial), final(_bound.final)
	{}

	bool Bound::contains(Point x) const {
		return initial.row <= x.row && x.row <= final.row &&
		initial.column <= x.column && x.column <= final.column;
	}

	Bound & Bound::operator += (const Point & x) {
		initial += x;
		final   += x;
		return * this;
	}

	Bound & Bound::operator -= (const Point & x) {
		initial -= x;
		final   -= x;
		return * this;
	}

	Bound & Bound::operator &= (const Bound & x) {
		initial = max(initial, x.initial);
		final   = min(final,   x.final);
		return * this;
	}

	Bound operator + (const Bound & _bound, const Point & _point) {
		Bound result(_bound);
		return result += _point;
	}

	Bound operator - (const Bound & _bound, const Point & _point) {
		Bound result(_bound);
		return result -= _point;
	}

	Bound operator & (const Bound & _a, const Bound & _b) {
		Bound result(_a);
		return result &= _b;
	}

	std::ostream & operator << (std::ostream & _ostream, const Bound & _bound) {
		_ostream << "Bound(" << _bound.initial << ", " << _bound.final << ")";
		return _ostream;
	}

}
