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

// square graphic library
namespace graphics {

	void square()
	{
		glPushMatrix();
		glTranslatef(FIGURE_OFFSET, FIGURE_OFFSET, 0);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, 0);
		glBegin(GL_POLYGON);
		/*glVertex2f(FIGURE_OFFSET, FIGURE_OFFSET);
		glVertex2f(FIGURE_OFFSET, FIGURE_BORDER);
		glVertex2f(FIGURE_BORDER, FIGURE_BORDER);
		glVertex2f(FIGURE_BORDER, FIGURE_OFFSET);
		*/
		glVertex2f(0, 0);
		glVertex2f(1, 0);
		glVertex2f(1, 1);
		glVertex2f(0, 1);
		glEnd();
		glPopMatrix();
	}

	void ngon(int angles = 5, int step_over = 1) {
		//float radius = FIGURE_SIZE / 2;
		const float radius = 0.5;
		int step = (360 / angles) * step_over;
		int loop_length = angles;
		int loops_count = 1;
		if((angles % step_over) == 0)
		{
			loop_length = angles / step_over;
			loops_count = step_over;
		}

		glPushMatrix();
		glTranslatef(0.5, 0.5, 0);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, 0);
		//glLineWidth(2);
		for(int j = 0; j < loops_count; j++) {
			//glBegin(GL_LINE_LOOP);
			glBegin(GL_POLYGON);
			for(int i = 0; i <= loop_length; i++) {
				float deg_in_rad = (j * (360 / angles) + i * step) * DEG2RAD;
				glVertex2f(cos(deg_in_rad) * radius, sin(deg_in_rad) * radius);
			}
			glEnd();
		}
		glPopMatrix();
	}

	void circle() {
		ngon(360);
	}

	void david() {
		ngon(6, 2);
	}

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

	enum ANIMATION {
		FADE,
		SCALE,
		SLIDE
	};

}

#endif
