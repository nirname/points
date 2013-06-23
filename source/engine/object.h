#ifndef OBJECT_H
#define OBJECT_H 1

namespace engine {

struct ObjectKind {
	static int count;
	int number;
	graphics::Shape * shape;
	graphics::Color * color;

	ObjectKind() {
		number = ++count;
	}
};

int ObjectKind::count = 0;
//typedef ObjectKind * ObjectKindPointer;

struct Object
	{
		static int count;
		//static std::map<ObjectKindType, int> count_of_kind;

		int number;
		//ObjectKindType kind;
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

		~Object() {
			//!!! remove its points
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
			if(kind != NULL && kind->shape != NULL) {
				kind->shape->display();
			} else graphics::square();
		}

		void use_color() {
			if(kind != NULL && kind->color != NULL) {
				kind->color->use();
			}
		}

		void display(const Point & _position);

	};

	std::ostream & operator << (std::ostream & _ostream, const Object & _object) {
		_ostream << "Object(" << _object.number << ")";
		return _ostream;
	}

	int Object::count = 0;


}

#endif
