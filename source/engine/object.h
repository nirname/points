#ifndef OBJECT_H
#define OBJECT_H 1

namespace engine {

	struct Object {

		static int count;

		int number;
		ObjectKindPointer kind;
		/*graphics::Shape * shape;
		graphics::Color * color;*/
		/*typedef std::list<graphics::Animation *> AnimationList;
		AnimationList animations;*/

		/*Object(const Object & _object) {
			type = _object.type;
			shape = _object.shape;
			color = _object.color;
			number = count++;
		}*/

		/*Object(graphics::Shape * _shape = NULL, graphics::Color * _color = NULL) :
			shape(_shape), color(_color)
		{
			number = count++;
		}*/
		Object() {
			number = count++;
		}

		Object(ObjectKindPointer _kind) : kind(_kind) {
			number = count++;
		}

		~Object() {
			// TODO: remove its points
			//--count;
		}

		//void place(Field *, Point _position);
		// returns true if moving was successed
		//bool move(Field *, Point _step, graphics::Animation * _animation);
		void go_to(Field * _field, Point _position);

		bool move(Field *, Point _step);
		//void rotate(Field * _field) {}
		//void symmetric(Field * _field) {}
		//transformation();

		/*struct Descendant
		{
			Point offset;
			Object * object;
			~Descendant() {
				delete object;
			}
		};*/

		//std::list<Object> descendants;
		//std::list<Points> mask;

		// make this one private
		void draw_shape() {
			if(kind != NULL) {
				kind->draw_shape();
			} else {
				graphics::square();
			}
		}

		void use_color() {
			if(kind != NULL) {
				kind->use_color();
			}
		}

		void display(const Point & _position);

		void print(std::ostream & _ostream) const {
			_ostream << "Object#" << number << " ("
				<< "kind: " << lib::to_string(kind)
			<< ")";
		}

	}; // class Object

	std::ostream & operator << (std::ostream & _ostream, const Object & _object) {
		_object.print(_ostream);
		return _ostream;
	}

	int Object::count = 0;

}


#endif
