#ifndef OBJECT_H
#define OBJECT_H 1

namespace engine {

struct Object
	{
		static int count;

		int number;
		ObjectKindType kind;
		graphics::Shape * shape;
		graphics::Color * color;

		/*Object(const Object & _object) {
			type = _object.type;
			shape = _object.shape;
			color = _object.color;
			number = count++;
		}*/

		Object(graphics::Shape * _shape = NULL, graphics::Color * _color = NULL) :
			shape(_shape), color(_color)
		{
			number = count++;
		}

		~Object() {
			//!!! remove its points
			//--count;
		}

		//void place(Field *, Point _position);
		void move(Field *, Point _step);
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
			if(shape != NULL) {
				shape->display();
			} else graphics::square();
		}

		void display(const Point & _position = Point()) { //, const Animation & = NULL
			glPushMatrix();
				glTranslatef(_position.column, _position.row, 0);
				glPushAttrib(GL_CURRENT_BIT);
					if(color != NULL) color->use();
					glPushMatrix(); // animation goes here
						glTranslatef(0.5, 0.5, 0);
						glScalef(scale, scale, 0);
						glTranslatef(-0.5, -0.5, 0);
						draw_shape();
					glPopMatrix();
					glPopAttrib();
			glPopMatrix();
		}
	};

	std::ostream & operator << (std::ostream & _ostream, const Object & _object) {
		_ostream << "Object(" << _object.number << ")";
		return _ostream;
	}

	int Object::count = 0;
	
	


}

#endif
