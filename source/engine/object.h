#pragma once

namespace engine {

	struct Object {

		static int count;

		int number;

		ObjectKindPointer kind;
		ObjectPoints mask; // TODO: move mask to object kind

		Object();
		Object(ObjectKindPointer);

		~Object();

		void initialize();

		void draw_shape();
		void use_color();

		void display(const ObjectPoints & _points);
		void display(const Point & _point);
		void print(std::ostream & _ostream) const;

	}; // class Object

	int Object::count = 0;

	Object::Object() {
		initialize();
		number = count++;
		kind = NULL;
	}

	Object::Object(ObjectKindPointer _kind) : kind(_kind) {
		initialize();
		number = count++;
	}
	
	Object::~Object() { }
	
	void Object::initialize() {
		mask.insert(Point(0, 0));
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

	void Object::display(const ObjectPoints & _points) {
		glPushAttrib(GL_CURRENT_BIT);
			use_color();
			for ( ObjectPoints::const_iterator
				i = _points.begin();
				i != _points.end();
				i++ )
			{
				glPushMatrix();
					glTranslatef(i->column, i->row, 0);
					draw_shape();
				glPopMatrix();
			}
		glPopAttrib();
	}

	// Displays only one point with
	// Animation, color and shape
	//
	void Object::display(const Point & _point) {
		glPushAttrib(GL_CURRENT_BIT);
			use_color();
			glPushMatrix();
				glTranslatef(_point.column, _point.row, 0);
				draw_shape();
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
