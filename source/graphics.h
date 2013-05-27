#ifndef GRAPHICS_H
#define GRAPHICS_H 1

#define EMPTY_SIZE 0.6f
#define FIGURE_SIZE 0.6f
const float FIGURE_OFFSET = (1.0 - FIGURE_SIZE) / 2;
//const float FIGURE_BORDER = FIGURE_SIZE + FIGURE_OFFSET;

//#define BLUE 20, 73, 233 // blue
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0
#define BLUE 17, 154, 255
#define YELLOW 255, 232, 17
#define GREEN 28, 174, 35
#define RED 235, 80, 80
#define AZURE 61, 222, 235
#define VIOLET 175, 0, 185
#define GRAY 127, 127, 127

const float DEG2RAD = 3.14159 / 180;

#include "graphics/drawing.h"

// square graphic library
namespace graphics {

	struct Color
	{
		positive red, green, blue;

		Color(positive _red, positive _green, positive _blue):
			red(_red), green(_green), blue(_blue)
		{}

		Color():
			red(0), green(0), blue(0)
		{}

		void use() {
			glColor3ub(red, green, blue);
		}
	};

	// Any shape
	struct Shape {
		// add size (radius, or something like that)
		virtual void display() = 0;
	};

	struct Square : public Shape {
		void display() {
			square();
		}
	};

	struct EmptySquare : public Shape {
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

	class Star : Shape {};

	struct David : Shape {
		void display() {
			david();
		}
	};

	enum ANIMATION_TYPE {
		NONE,
		FADE,
		SCALE,
		SLIDE
	};

}

#endif
