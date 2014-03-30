#pragma once

namespace engine {

	struct ObjectKind {

		static int count;
		int number;
		graphics::Shape * shape;
		graphics::Color * color;

		ObjectKind() {
			shape = NULL;
			color = NULL;
			number = ++count;
		}

		void draw_shape();
		void use_color();
		void print(std::ostream & _ostream) const;

	}; // class ObjectKind

	int ObjectKind::count = 0;

	void ObjectKind::draw_shape() {
		if(shape != NULL) {
			shape->display();
		} else {
			graphics::default_shape();
		}
	}

	void ObjectKind::use_color() {
		if(color != NULL) {
			color->use();
		}
	}

	void ObjectKind::print(std::ostream & _ostream) const {
		_ostream << "ObjectKind#" << number << " ("
			<< "color: " << lib::to_string(color) << ", "
			<< "shape: " << lib::to_string(shape)
		<< ")";
	}

	std::ostream & operator << (std::ostream & _ostream, const ObjectKind & _object_kind) {
		_object_kind.print(_ostream);
		return _ostream;
	}

}
