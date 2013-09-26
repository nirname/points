#ifndef FIELD_H
#define FIELD_H 1

namespace engine {

	// make this types splitted by dimensions
	enum CLOSURE_TYPE
	{
		NO_CLOSURE,
		VERTICAL_CLOSURE,
		HORIZONTAL_CLOSURE,
		FULL_CLOSURE
	};

	// make this types splitted by dimensions
	enum INFINITY_TYPE
	{
		FINITE,
		VERTICAL_INFINITY,
		HORIZONTAL_INFINITY,
		FULL_INFINITY
	};

	struct Field
	{
		static int count;
		int number;
		Size size;
		CLOSURE_TYPE closure;
		Data data;

		Field(int _width = 1, int _height = 1) {
			size = Size(_width, _height);
			number = count++;
		}

		~Field() {}

		INFINITY_TYPE infinity_type() {
			return INFINITY_TYPE(
				(size.height == 0 ? VERTICAL_INFINITY : FINITE) |
				(size.width == 0 ? HORIZONTAL_INFINITY : FINITE)
			);
		}

		Bound bound() {
			return Bound(Point(size.width, size.height) - Point(1, 1)); //shift
		}

		void print(std::ostream & _ostream) const {
			_ostream << "Field#" << number;
		}

	}; // Field

	int Field::count = 0;

	std::ostream & operator << (std::ostream & _ostream, const Field & _field) {
		_field.print(_ostream);
		return _ostream;
	}

	void operator >> (const YAML::Node & options, Field & field) {
		if(options.IsMap()) {
			if(options["size"]) {
				options["size"] >> field.size;
			}
		} else {
			std::cout << "Options for field should be a mapping" << std::endl;
		}
	}

} // namespace engine


#endif
