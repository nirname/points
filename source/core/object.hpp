#pragma once

#include "opengl.hpp"

#include "point.hpp"
#include "object_kind.hpp"


struct Object {

	ObjectKind * kind;
	//ObjectPoints mask; // TODO: move mask to object kind

	Object();
	~Object();

	void initialize();

	void draw_shape();
	void use_color();

	//void display(const ObjectPoints & _points);
	void display(const Point & _point);

}; // class Object


Object::Object() {
	kind = NULL;
}

void Object::draw_shape() {
	if(kind != NULL) {
		kind->draw_shape();
	}
}

void Object::use_color() {
	if(kind != NULL) {
		kind->use_color();
	}
}

/*void Object::display(const ObjectPoints & _points) {
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
}*/

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
