#pragma once

namespace engine {

	struct Bound {
		Point initial, final;

		Bound(const Point & _final):
			final(_final)
		{}

		Bound(Point _initial, Point _final):
			initial(_initial), final(_final)
		{ /* do not normilize here*/ }

		Bound(const Bound & _bound):
			initial(_bound.initial), final(_bound.final)
		{}

		bool contains(Point x) const {
			//return initial <= x && x <= final;
			return initial.row <= x.row && x.row <= final.row &&
			initial.column <= x.column && x.column <= final.column;
			//return false;
		}

		Bound & operator += (const Point & x) {
			initial += x;
			final   += x;
			return * this;
		}

		Bound & operator -= (const Point & x) {
			initial -= x;
			final   -= x;
			return * this;
		}

		// intersection
		Bound & operator &= (const Bound & x) {
			initial = max(initial, x.initial);
			final   = min(final,   x.final);
			return * this;
		}

	};

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
