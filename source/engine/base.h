#ifndef BASE_H
#define BASE_H 1

// TODO: split into two files for each class
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

// TODO: move it from here
namespace graphics {

	void grid(const engine::Bound & _bound, Color * _color = NULL) {
		glPushAttrib(GL_CURRENT_BIT);
			if(_color != NULL) {
				_color->use();
			} else {
				glColor3ub(BLACK);
			}
			glBegin(GL_LINES);
				if(_bound.initial.row < _bound.final.row) {
					for(int x = _bound.initial.column; x <= _bound.final.column; x++) {
						glVertex2f(x, _bound.initial.row);
						glVertex2f(x, _bound.final.row);
					}
				}
				if(_bound.initial.column < _bound.final.column) {
					for(int y = _bound.initial.row; y <= _bound.final.row; y++) {
						glVertex2f(_bound.initial.column, y);
						glVertex2f(_bound.final.column, y);
					}
				}
			glEnd();
		glPopAttrib();
	}


}

#endif
