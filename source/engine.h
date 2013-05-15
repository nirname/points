#ifndef ENGINE_H
#define ENGINE_H 1

// engine
namespace engine {

	struct Point
	{
		int row;
		int column;
		Point(int _row = 0, int _column = 0):
			row(_row), column(_column)
		{}
	};

	struct Cell
	{
		graphics::Color * color;
		graphics::Shape * shape;
		//Cell(graphics::Color _color, graphics::Shape * shape)
	};

	//class Figure {};

	struct Size
	{
		positive width;
		positive height;
		Size(positive _width = 1, positive _height = 1):
			width(_width), height(_height)
		{}
	};

	struct Field
	{
		Size size;
		Field(positive _width = 1, positive _height = 1)
		{
			size = Size(_width, _height);
		}
	};

	// Contains width and height expressed by count of horizontal and vertical squares
	struct Screen {
		float width, height, margin;
		Screen(float _width = 10.0, float _height = 10.0, float _margin = 0.0):
			width(_width), height(_height), margin(_margin)
		{}
	};

	// Displays part of specified field
	// at specified position at screen
	struct View
	{
		Field * field;
		Size size; // view size; by default it is the same as field size is
		Point offset; // field offset
		//Screen * screen;
		Point position; // position at screen

		View(Field * _field)
		{
			field = _field;
			size = _field->size;
			offset = Point(0, 0);
		}

		void display()
		{
			// drawing grid
			glLineWidth(2);
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
			// drawing points
		}
	};

	// Describes current game
	struct Game {

		logic::GAME_KIND game_kind;
		//engine::Screen screen;
		lib::List<engine::Field> fields;
		lib::List<engine::View> areas;

		std::unordered_map<std::string, graphics::Color * > colors;
		std::unordered_map<std::string, graphics::Shape * > shapes;

		Game(logic::GAME_KIND _game_kind):
			game_kind(_game_kind)
		{}
	};

	/*struct Object
	{
		lib::List<Point> points;
	}*/

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
