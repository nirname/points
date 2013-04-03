#ifndef GRAPHICS_H
#define GRAPHICS_H 1

//#define BLUE 20, 73, 233 // blue
#define BLUE 17, 154, 255
#define YELLOW 255, 232, 17
#define GREEN 28, 174, 35
#define RED 235, 80, 80
#define AZURE 61, 222, 235
#define VIOLET 175, 0, 185
#define GRAY 127, 127, 127

// square graphic library
namespace sgl {

	struct Color
	{
		positive red, green, blue;

		Color(positive _red, positive _green, positive _blue):
			red(_red), green(_green), blue(_blue)
		{}

		Color():
			red(0), green(0), blue(0)
		{}
	};

	void square()
	{
		glBegin(GL_POLYGON);
		glVertex2f(0.05f, 0.05f);
		glVertex2f(0.05f, 0.95f);
		glVertex2f(0.95f, 0.95f);
		glVertex2f(0.95f, 0.05f);
		glEnd();
	}

	void draw_at(int x, int y, void(*display)())
	{
		glPushMatrix();
		glTranslatef(x, y, 0);
		display();
		glPopMatrix();
	}
}

#endif
