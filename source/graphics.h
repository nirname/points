#ifndef GRAPHICS_H
#define GRAPHICS_H 1

#define EMPTY_SIZE 0.6f
#define FIGURE_SIZE 0.8f
const float FIGURE_OFFSET = (1.0 - FIGURE_SIZE) / 2.0;
//const float FIGURE_BORDER = FIGURE_SIZE + FIGURE_OFFSET;

const float DEG2RAD = 3.14159 / 180;

#include "graphics/color.h"
#include "graphics/drawing.h"
#include "graphics/animation.h"

// graphic library
namespace graphics {

	// Any shape
	struct Shape {
		float figure_size;
		// add size (radius, or something like that)
		virtual void display() = 0;
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

	struct EmptyStar : Star {
		void display() {
			//emptiness(Star::display);
		}
	};

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

}

#endif
