#ifndef GRAPHICS_H
#define GRAPHICS_H 1

#define FIGURE_SIZE 0.6f
const float FIGURE_OFFSET = (1.0 - FIGURE_SIZE) / 2;
const float FIGURE_BORDER = FIGURE_SIZE + FIGURE_OFFSET;

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

	struct Color
	{
		positive red, green, blue;

		Color(positive _red, positive _green, positive _blue):
			red(_red), green(_green), blue(_blue)
		{}

		Color():
			red(0), green(0), blue(0)
		{}

		void set() {
			glColor3ub(red, green, blue);
		}
	};

	void square()
	{
		glBegin(GL_POLYGON);
		glVertex2f(FIGURE_OFFSET, FIGURE_OFFSET);
		glVertex2f(FIGURE_OFFSET, FIGURE_BORDER);
		glVertex2f(FIGURE_BORDER, FIGURE_BORDER);
		glVertex2f(FIGURE_BORDER, FIGURE_OFFSET);
		glEnd();
	}

	void circle(float radius = FIGURE_SIZE / 2) {
		glBegin(GL_POLYGON); // GL_LINE_LOOP
		for (int i=0; i < 360; i++)
		{
			float deg_in_rad = i * DEG2RAD;
			glVertex2f(cos(deg_in_rad) * radius, sin(deg_in_rad) * radius);
		}
		glEnd();
	}

	// Any shape
	class Shape
	{
		protected:
			graphics::Color * color;
		public:
			virtual void display() = 0;
	};

	class Square : public Shape
	{
		public:
			Square(graphics::Color * _color = NULL) {
				color = _color;
			}
			void display()
			{
				if(color != NULL) color->set();
				graphics::square();
			}
	};

	class Circle : Shape
	{
		public:
			Circle(graphics::Color * _color = NULL) {
				color = _color;
			}
			void display()
			{
				if(color != NULL) color->set();
				circle(FIGURE_SIZE / 2);
			}
	};

	void draw_at(int x, int y, void(*display)())
	{
		glPushMatrix();
		glTranslatef(x, y, 0);
		display();
		glPopMatrix();
	}

}

#endif
