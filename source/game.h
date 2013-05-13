#ifndef GAME_H
#define GAME_H 1

// game logic
namespace logic {

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

	// Describes current game
	class Game {
		GAME_KIND game_kind;
		//engine::Screen screen;
		lib::List<engine::Field> fields;
		lib::List<engine::View> areas;
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


}

#endif
