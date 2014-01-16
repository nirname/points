#pragma once

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

}
