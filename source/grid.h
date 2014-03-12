#pragma once

namespace graphics {

	void line(int x1, int y1, int x2, int y2) {
		glBegin(GL_LINES);
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
		glEnd();
	}

	//glPushAttrib(GL_ENABLE_BIT);
	//glLineStipple(1, 0xAAAA);
	//if(x % 10 != 0) glEnable(GL_LINE_STIPPLE);
	//glDisable(GL_LINE_STIPPLE);
	void grid(const engine::Bound & _bound, int _step) {
		if(_bound.initial.row < _bound.final.row) {
			for(int x = _bound.initial.column; x <= _bound.final.column; x += _step) {
				line(x, _bound.initial.row, x, _bound.final.row);
			}
		}
		if(_bound.initial.column < _bound.final.column) {
			for(int y = _bound.initial.row; y <= _bound.final.row; y += _step) {
				line(_bound.initial.column, y, _bound.final.column, y);
			}
		}
	}

}
