#ifndef ENGINE_PRIMITIVES
#define ENGINE_PRIMITIVES 1

namespace engine {
	
	struct Point {
		int row;
		int column;

		Point(const Point & x):
			column(x.column), row(x.row)
		{}

		Point(int _column = 0, int _row = 0):
			column(_column), row(_row)
		{}

		Point & operator += (const Point & x) {
			row    += x.row;
			column += x.column;
			return * this;
		}

		Point & operator -= (const Point & x) {
			row    -= x.row;
			column -= x.column;
			return * this;
		}

		Point & operator *= (const Point & x) {
			row    *= x.row;
			column *= x.column;
			return * this;
		}

		bool operator < (const Point & x) const {
			return column < x.column && row < x.row;
		}

		bool operator <= (const Point & x) const {
			return column <= x.column && row <= x.row;
		}

	};

	std::ostream & operator << (std::ostream & _ostream, const Point & _point) {
		_ostream << "Point(" << _point.column << ", " << _point.row << ")";
	}

	Point operator + (const Point & a, const Point & b) {
		Point result(a);
		return result += b;
	}

	Point operator - (const Point & a, const Point & b) {
		Point result(a);
		return result -= b;
	}

	Point operator * (const Point & a, const Point & b) {
		Point result(a);
		return result *= b;
	}

	Point min(Point a, Point b) {
		return Point(
			std::min(a.column, b.column),
			std::min(a.row, b.row)
		);
	}

	Point max(Point a, Point b) {
		return Point(
			std::max(a.column, b.column),
			std::max(a.row, b.row)
		);
	}

	struct Size {
		int width;
		int height;
		Size(int _width = 1, int _height = 1):
			width(_width), height(_height)
		{}
	};

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
			return initial <= x && x <= final;
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
	};

	std::ostream & operator << (std::ostream & _ostream, const Bound & _bound) {
		_ostream << "Bound(" << _bound.initial << ", " << _bound.final << ")";
		return _ostream;
	}

	Bound operator + (const Bound & _bound, const Point & _point) {
		Bound result(_bound);
		return result += _point;
	}
	/*Bound operator - (Bound _bound, Point _point)
		/*Bound result = _bound;
		return result -= _point;
	}*/
	
}

#endif
