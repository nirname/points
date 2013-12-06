#ifndef BASE_H
#define BASE_H 1

#include "base/point.h"
#include "base/size.h"
#include "base/bound.h"

// TODO: move it from here
namespace graphics {

	void grid(const engine::Bound & _bound, Color * _color = NULL) {
		glPushAttrib(GL_CURRENT_BIT);
			if(_color != NULL) {
				_color->use();
			} else {
				glColor3ub(BLACK);
			}
			glBegin(GL_LINES);
				if(_bound.initial.row < _bound.final.row) {
					for(int x = _bound.initial.column; x <= _bound.final.column; x++) {
						glVertex2f(x, _bound.initial.row);
						glVertex2f(x, _bound.final.row);
					}
				}
				if(_bound.initial.column < _bound.final.column) {
					for(int y = _bound.initial.row; y <= _bound.final.row; y++) {
						glVertex2f(_bound.initial.column, y);
						glVertex2f(_bound.final.column, y);
					}
				}
			glEnd();
		glPopAttrib();
	}


}

#endif
