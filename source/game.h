#ifndef GAME_H
#define GAME_H 1

// game logic
namespace logic {

	enum GAME_KIND
	{
		SOKOBAN, // ���������
		SNAKE, // ������
		LABYRINTH, // ������� ��������
		PENTAMINO, // ����������� ����� �����
		TETRIS, // ������
		LANGO, // �������
		LIGHTS, // ��������� ����
		LINES, // �����
		FOUR_IN_A_ROW, // ������ � ���
		SWAP, // ����� ���� ������ � ����������� �����
		ROBOTS, // ������� �� �������

		GOMOKU, // �������� ������
		SUDOKU, // ������
		SAPPER, //MINES, // ����
		NONOGRAM, // �������� ����������
		SEA, // ������� ���
		THRONE, // ������ ��� ����� ������
		POINTS, // go
		// � � ��� �� ����, �� ��� �����
		JEZZ_BELL,
		ATOMIX,
		BACKGAMMON, // �����
		CHECKERS // �����
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
		LINE = 07, // �����������, ���������, ��� ���������
		RECTANGLE = 010,
		ANY_BLOCK = 017
	};

	// ���������� ��������� ����������� � ���� ����
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
