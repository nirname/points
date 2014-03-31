#pragma once

namespace engine {

	struct Object {

		static int count;

		int number;
		
		ObjectKindPointer kind;
		ObjectPoints mask;
		/*typedef std::list<graphics::Animation *> AnimationList;
		AnimationList animations;*/

		Object();
		Object(ObjectKindPointer);

		~Object();

		//bool move(Field *, Point _step, graphics::Animation * _animation);
		bool move(Field *, Point _step);
		void go_to(Field * _field, Point _position);

		//void rotate(Field * _field) {}
		//void symmetric(Field * _field) {}
		//transformation();

		void draw_shape();
		void use_color();

		void display(const Point & _position);
		void print(std::ostream & _ostream) const;

	}; // class Object

	int Object::count = 0;

	Object::Object() {
		number = count++;
		kind = NULL;
	}

	Object::Object(ObjectKindPointer _kind) : kind(_kind) {
		number = count++;
	}
	
	void Object::draw_shape() {
		if(kind != NULL) {
			kind->draw_shape();
		} else {
			graphics::default_shape();
		}
	}
	
	void Object::use_color() {
		if(kind != NULL) {
			kind->use_color();
		}
	}

	Object::~Object() {
		// TODO: remove its points
		//--count;
	}

	void Object::display(const Point & _position = Point()) {
		//, const Animation & = NULL
		glPushAttrib(GL_CURRENT_BIT);
			//graphics::use_color(color);
			use_color();
			glPushMatrix();
				glTranslatef(_position.column, _position.row, 0);
					glPushMatrix(); // animation goes here
					/*for(AnimationList::iterator a = animations.begin(); a != animations.end(); ++a) {
						(*a)->apply();
					}*/
					//game.animations["Scale"]->apply();
					/*glTranslatef(0.5, 0.5, 0);
					glScalef(scale, scale, 0);
					glTranslatef(-0.5, -0.5, 0);*/
					draw_shape();
					//graphics::square();
				glPopMatrix();
			glPopMatrix();
		glPopAttrib();
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

}
