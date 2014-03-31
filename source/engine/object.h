#pragma once

namespace engine {

	struct Object {

		static int count;

		int number;
		ObjectKindPointer kind;
		/*typedef std::list<graphics::Animation *> AnimationList;
		AnimationList animations;*/

		Object();
		Object(ObjectKindPointer);

		~Object() {
			// TODO: remove its points
			//--count;
		}

		//bool move(Field *, Point _step, graphics::Animation * _animation);
		bool move(Field *, Point _step);
		void go_to(Field * _field, Point _position);

		//void rotate(Field * _field) {}
		//void symmetric(Field * _field) {}
		//transformation();

		// make this one private
		void draw_shape() {
			if(kind != NULL) {
				kind->draw_shape();
			} else {
				graphics::default_shape();
			}
		}

		void use_color() {
			if(kind != NULL) {
				kind->use_color();
			}
		}

		void display(const Point & _position);
		void print(std::ostream & _ostream) const;

	}; // class Object

	Object::Object() {
		number = count++;
		kind = NULL;
	}
	
	Object::Object(ObjectKindPointer _kind) : kind(_kind) {
		number = count++;
	}
	
	void Object::print(std::ostream & _ostream) const {
		_ostream << "Object#" << number << " ("
			<< "kind: " << lib::to_string(kind)
		<< ")";
	}

	std::ostream & operator << (std::ostream & _ostream, const Object & _object) {
		_object.print(_ostream);
		return _ostream;
	}

	int Object::count = 0;

}
