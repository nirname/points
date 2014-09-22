#include "point.hpp"
#include "bound.hpp"

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

// Get another shifted bound
Bound operator + (const Bound & _bound, const Point & _point) {
	Bound result(_bound);
	return result += _point;
}

// Get another shifted bound
Bound operator - (const Bound & _bound, const Point & _point) {
	Bound result(_bound);
	return result -= _point;
}

// Get intersection of bounds
Bound operator & (const Bound & _a, const Bound & _b) {
	Bound result(_a);
	return result &= _b;
}

/*std::ostream & operator << (std::ostream & _ostream, const Bound & _bound) {
	_ostream << "Bound(" << _bound.initial << ", " << _bound.final << ")";
	return _ostream;
}*/
