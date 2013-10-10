#ifndef LOGIC_H
#define LOGIC_H 1

// game logic
// (!!!) remove logic file at all?
namespace logic {

	enum GAME_KIND
	{
		SOKOBAN, // кладовщик
		SNAKE, // змейка
		LABYRINTH, // обычный лабиринт / написать генератор лабиринтов
		PENTAMINO, // расставлять набор фигур
		TETRIS, // тетрис
		LANGO, // реверси
		LIGHTS, // выключить свет
		LINES, // линии
		FOUR_IN_A_ROW, // четыре в ряд
		SWAP, // обмен двух клеток и схлопывание рядов
		ROBOTS, // Убегать от роботов
		PAINTER, // Закрасить как можно больше клеток (всё поле)
		GOMOKU, // Крестики нолики
		SUDOKU, // судоку
		SAPPER, //MINES, // сапёр
		NONOGRAM, // японские кроссворды
		SEA, // морской бой
		THRONE, // выжить как можно дольше
		POINTS, // go
		RUSH_OUR, // машина должна выехать со стоянки
		FIGURE_GROUND, // передвигать области. замкнутые области становятся самостоятельными
		// я и сам не знаю, чё это такое
		JEZZ_BELL,
		ATOMIX,
		BACKGAMMON, // нарды
		CHECKERS // шашки
	};

	/*class Cursor
	{};*/


}

#endif
