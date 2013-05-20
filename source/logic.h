#ifndef LOGIC_H
#define LOGIC_H 1

// game logic
namespace logic {

	enum GAME_KIND
	{
		SOKOBAN, // кладовщик
		SNAKE, // змейка
		LABYRINTH, // обычный лабиринт
		PENTAMINO, // расставлять набор фигур
		TETRIS, // тетрис
		LANGO, // реверси
		LIGHTS, // выключить свет
		LINES, // линии
		FOUR_IN_A_ROW, // четыре в ряд
		SWAP, // обмен двух клеток и схлопывание рядов
		ROBOTS, // Убегать от роботов

		GOMOKU, // Крестики нолики
		SUDOKU, // судоку
		SAPPER, //MINES, // сапёр
		NONOGRAM, // японские кроссворды
		SEA, // морской бой
		THRONE, // выжить как можно дольше
		POINTS, // go
		// я и сам не знаю, чё это такое
		JEZZ_BELL,
		ATOMIX,
		BACKGAMMON, // нарды
		CHECKERS // шашки
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

	// объединяет несколько квадратиков в один блок
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
