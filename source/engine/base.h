#ifndef BASE_H
#define BASE_H 1

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
			return row < x.row || (row == x.row && column < x.column);
		}

		/*bool operator <= (const Point & x) const {
			return row <= x.row && column <= x.column;
		}*/

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

	void operator >> (const YAML::Node & options, Size & size) {
		try {
			if(options.IsMap()) {
				if(options["width"] != NULL && options["height"] != NULL) {
					size.width = options["width"].as<int>();
					size.height = options["height"].as<int>();
				}
			} else if (options.IsSequence()) {
				if(options.size() == 1) {
					size.height = size.width = options[0].as<int>();
				} else if(options.size() == 2) {
					size.width = options[0].as<int>();
					size.height = options[1].as<int>();
				} else {
					std::cout << "Wrong number of arguments for size" << std::endl;
				}
			} else if (options.IsScalar()) {
				size.height = size.width = options.as<int>();
			} else {
				std::cout << "Size options should be scalar or map" << std::endl;
			}
		} catch(YAML::TypedBadConversion<int> & exception) {
			std::cout << "Size should be an integer " << std::endl;
			size.width = 1;
			size.height = 1;
		}
	}

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

#endif
