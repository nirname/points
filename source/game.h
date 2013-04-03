#ifndef GAME_H
#define GAME_H 1

// game logic
namespace gml {

	enum GAME_KIND
	{
		SOKOBAN, // кладовщик
		SNAKE, // змейка
		LABYRINTH, // обычный лабиринт
		PENTAMINO, // расставл€ть набор фигур
		TETRIS, // тетрис
		LANGO, // реверси
		LIGHTS, // выключить свет
		LINES, // линии
		FOUR_IN_A_ROW, // четыре в р€д
		SWAP, // обмен двух клеток и схлопывание р€дов
		ROBOTS, // ”бегать от роботов

		GOMOKU, //  рестики нолики
		SUDOKU, // судоку
		SAPPER, //MINES, // сапЄр
		NONOGRAM, // €понские кроссворды
		SEA, // морской бой
		THRONE, // выжить как можно дольше
		POINTS, // go
		// € и сам не знаю, чЄ это такое
		JEZZ_BELL,
		ATOMIX,
		BACKGAMMON, // нарды
		CHECKERS // шашки
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
			Field(int _width, int _height): width(_width), height(_height) {};
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
						sgl::draw_at(x, y, sgl::square);
					}
				}
			};
	};

	// Describes current game
	class Game {
		GAME_KIND game_kind;
		Field field;
		lib::List<Area> areas;
	};

	/*enum BLOCK_TYPE
	{
		HORIZONTAL = 01,
		VERTICAL = 02,
		DIAGONAL = 04,
		LINE = 07, // горизонталь, вертикаль, или диагональ
		RECTANGLE = 010,
		ANY_BLOCK = 017
	};

	// объедин€ет несколько квадратиков в один блок
	class Block
	{
		BLOCK_TYPE type;
		Position begin;
		Position end;

		Block(BLOCK_TYPE _type, Position _begin, Position _end) :
			type(_type), begin(_begin), end(_end)
		{}

		public:

		bool is_line() {
			return type & LINE;
		}

	};*/

	/*class Cursor
	{};*/

	class Object;
	class Placement;
	class Figure;
	class Square;

	class Object {};

	// Placement of any object
	class Placement
	{
		// area or field should be there?
		Position position;
		Object * object;
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

	class Shape : Object
	{
		protected:
			sgl::Color * color;
		public:
			virtual void display();
	};

	class Square : Shape
	{
		public:
			Square(sgl::Color * _color)
			{
				color = _color;
			}
			void display()
			{
				sgl::square();
			}
	};


}

#endif
