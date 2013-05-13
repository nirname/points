#ifndef ENGINE_H
#define ENGINE_H 1

// engine
namespace engine {

	class Point
	{
		int row;
		int column;
		public:
			Point(int _row = 0, int _column = 0):
				row(_row), column(_column)
			{}
	};

	struct Size
	{
		positive width;
		positive height;
		public:
			Size(positive _width = 1, positive _height = 1):
				width(_width), height(_height)
			{}
	};

	class Field
	{
		Size size;
		public:
			Field(positive _width = 1, positive _height = 1)
			{
				size = Size(_width, _height);
			}
			void display()
			{
				glLineWidth(3);
				/*glBegin(GL_LINES);
				glVertex2f(1, 1);
				glVertex2f(1, 5);
				glEnd();*/
				glBegin(GL_LINES);
				for(positive i = 0; i <= size.width; i++) {
					glVertex2f(i, 0);
					glVertex2f(i, size.height);
				}
				for(positive i = 0; i <= size.height; i++) {
					glVertex2f(0, i);
					glVertex2f(size.width, i);
				}
				glEnd();
			}
	};

	struct Screen {
		Size size;
		public:
			Screen(positive _width = 1, positive _height = 1)
			{
				size = Size(_width, _height);
			}
	};

	class View
	{
		Size size;
		Field * field;
		Screen * screen;
		Point offset;
	};

	// Placement of any object
	/*class Placement
	{
		// area or field should be there?
		//Position position;
		//Object * object;
	};

	// Two dimensional position
	class Position
	{
		private:
			int row; // number of row
			int column; // number of column
		public:
			Position(int _row = 0, int _column = 0):
				row(_row), column(_column)
			{}
	};
/*
	enum SPACE_TYPE
	{
		NO_CLOSURE         = 00,
		VERTICAL_CLOSURE   = 01,
		HORIZONTAL_CLOSURE = 02,
		FULL_CLOSURE       = 03,
		INFINITE_FIELD     = 04
	};

	class Field
	{
		private:
			int width;
			int height;
		public:
			Field(int _width, int _height):
				width(_width), height(_height)
			{};
	};

	class Area
	{
		private:
			SPACE_TYPE space_type;
			Position   origin;
			int width;
			int height;
		public:
			Area(int _width, int _height, Position _origin, SPACE_TYPE _space_type = NO_CLOSURE):
			width(_width), height(_height), origin(_origin), space_type(_space_type)
			{}
			void display()
			{
				for(int y = 0; y < height; y++)
				{
					for(int x = 0; x < width; x++)
					{
						graphics::draw_at(x, y, graphics::square);
					}
				}
			};
	};

	// Combination of shapes
	class Figure : Object
	{
		private:
			lib::List<Shape> shapes;
		public:
			void add(Shape * shape)
			{
				//squares
			};
	};

*/
} // engine

#endif
