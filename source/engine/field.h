#pragma once

namespace engine {

	// Make this types splitted by dimensions
	enum INFINITY_TYPE {
		FINITE,
		VERTICAL_INFINITY,
		HORIZONTAL_INFINITY,
		FULL_INFINITY
	};

	struct Field {

		static int count;
		int number;
		Size size;
		CLOSURE_TYPE closure;
		Data data;
		std::set<Point> cells;

		Field(int _width = 1, int _height = 1);
		~Field();

		INFINITY_TYPE infinity_type();
		Bound bound();
		void print(std::ostream &) const;

	}; // Field

	int Field::count = 0;

	Field::Field(int _width, int _height) {
		size = Size(_width, _height);
		number = count++;
	}

	Field::~Field() {
		data.clear();
	}

	Bound Field::bound() {
		return Bound(Point(size.width, size.height) - Point(1, 1));
	}

	INFINITY_TYPE Field::infinity_type() {
		return INFINITY_TYPE(
			(size.height == 0 ? VERTICAL_INFINITY : FINITE) |
			(size.width == 0 ? HORIZONTAL_INFINITY : FINITE)
		);
	}

	void Field::print(std::ostream & _ostream) const {
		_ostream << "Field#" << this;
	}

	std::ostream & operator << (std::ostream & _ostream, const Field & _field) {
		_field.print(_ostream);
		return _ostream;
	}

}
