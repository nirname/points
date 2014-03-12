#ifndef SHAPE_H
#define SHAPE_H 1

// graphic library
namespace graphics {

	// Any shape
	struct Shape {
		float size;

		virtual void display() = 0;

		void print(std::ostream & _ostream) const {
			_ostream << "Shape#" << this;
		}

	};

	struct Square : public Shape {
		void display() {
			square();
		}
	};

	/*void emptiness(void (Shape::*display)()){
		display();
		glPushMatrix();
			glTranslatef((1.0 - EMPTY_SIZE) / 2, (1.0 - EMPTY_SIZE) / 2, 0);
			glScalef(EMPTY_SIZE, EMPTY_SIZE, 0);
			glPushAttrib(GL_CURRENT_BIT);
				glColor3ub(WHITE);
				display();
			glPopAttrib();
		glPopMatrix();
	}*/

	struct Star : Shape {
		void display() {
			star();
		}
	};

	/*struct EmptyStar : Star {
		void display() {
			//emptiness(Star::display);
		}
	};*/

	struct EmptySquare : Shape {
		void display() {
			square();
			glPushMatrix();
				glTranslatef((1.0 - EMPTY_SIZE) / 2, (1.0 - EMPTY_SIZE) / 2, 0);
				glScalef(EMPTY_SIZE, EMPTY_SIZE, 0);
				glPushAttrib(GL_CURRENT_BIT);
					glColor3ub(WHITE);
					square();
				glPopAttrib();
			glPopMatrix();
		}
	};

	struct Circle : Shape {
		void display() {
			circle();
		}
	};

	struct Ring : Shape {
		void display() {
			circle();
			glPushMatrix();
				glTranslatef((1.0 - EMPTY_SIZE) / 2, (1.0 - EMPTY_SIZE) / 2, 0);
				glScalef(EMPTY_SIZE, EMPTY_SIZE, 0);
				glPushAttrib(GL_CURRENT_BIT);
					glColor3ub(WHITE);
					circle();
				glPopAttrib();
			glPopMatrix();
		}
	};

	struct NGon : Shape {
		int angles, step_over;
		NGon(int _angles = 6, int _step_over = 1) {
			angles = _angles;
			step_over = _step_over;
		}
		void display() {
			ngon(angles, step_over);
		}
	};

	struct David : Shape {
		void display() {
			david();
		}
	};

	struct Retro : Shape {
		void display() {
			square();
			glPushMatrix();
				glTranslatef((1.0 - EMPTY_SIZE) / 2, (1.0 - EMPTY_SIZE) / 2, 0);
				glScalef(EMPTY_SIZE, EMPTY_SIZE, 0);
				glPushAttrib(GL_CURRENT_BIT);
					glColor3ub(WHITE);
					square();
				glPopAttrib();
				glPushMatrix();
					glTranslatef((1.0 - EMPTY_SIZE) / 2, (1.0 - EMPTY_SIZE) / 2, 0);
					glScalef(EMPTY_SIZE, EMPTY_SIZE, 0);
						square();
				glPopMatrix();
			glPopMatrix();
		}
	};

	std::ostream & operator << (std::ostream & _ostream, const Shape & _shape) {
		_shape.print(_ostream);
		return _ostream;
	}

}

#endif
