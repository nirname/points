#include "object.hpp"

#include "opengl.hpp"

Object::Object() {
	kind = NULL;
}

void Object::draw_shape() const {
	if(kind != NULL) {
		kind->draw_shape();
	}
}

void Object::use_color() const {
	if(kind != NULL) {
		kind->use_color();
	}
}

void Object::display(const PointSet & point_set) const {
	glPushAttrib(GL_CURRENT_BIT);
		use_color();
		for ( PointSet::const_iterator
			i = point_set.begin();
			i != point_set.end();
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
void Object::display(const Point & _point) const {
	glPushAttrib(GL_CURRENT_BIT);
		use_color();
		glPushMatrix();
			glTranslatef(_point.column, _point.row, 0);
			draw_shape();
		glPopMatrix();
	glPopAttrib();
}
