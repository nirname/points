#pragma once

enum GAME_KIND {

	// Single player

	SNAKE = 0x00,
	SOKOBAN,
	ATOMIX,
	RUSH_HOUR,
	LIGHTS,
	TETRIS,
	ROBOTS,
	LABYRINTH,
	SWAP,
	POLYMINO,
	BACKGROUND,
	LINES,
	NETWALK,
	MOWER,
	MASYU,
	RINGS,
	BOMBERMAN,
	PACMAN,
	GAME1024,

	// Multiplayer

	REVERSI,
	GOMOKU,
	FOUR_IN_A_ROW,
	TRHONE,
	BATTLESHIP,
	POINTS,
	GO,
	STICS,
	CORNERS

};


std::ostream & operator << (std::ostream & _ostream, const GAME_KIND _game_kind) {
	switch(_game_kind) {
		case SNAKE: _ostream << "Snake"; break;
		case SOKOBAN: _ostream << "Sokoban"; break;
		case ATOMIX: _ostream << "Atomix"; break;
		case RUSH_HOUR: _ostream << "Rush hour"; break;
		case LIGHTS: _ostream << "Lights"; break;
		case TETRIS: _ostream << "Tetris"; break;
		case ROBOTS: _ostream << "Robots"; break;
		case LABYRINTH: _ostream << "Labyrinth"; break;
		case SWAP: _ostream << "Swap"; break;
		case POLYMINO: _ostream << "Polymino"; break;
		case BACKGROUND: _ostream << "Background"; break;
		case LINES: _ostream << "Lines"; break;
		case NETWALK: _ostream << "Netwalk"; break;
		case MOWER: _ostream << "Mower"; break;
		case MASYU: _ostream << "Masyu"; break;
		case RINGS: _ostream << "Rings"; break;
		case BOMBERMAN: _ostream << "Bomberman"; break;
		case PACMAN: _ostream << "Pacman"; break;
		case GAME1024: _ostream << "1024"; break;
		case REVERSI: _ostream << "Reversi"; break;
		case GOMOKU: _ostream << "Gomoku"; break;
		case FOUR_IN_A_ROW: _ostream << "Four in a row"; break;
		case TRHONE: _ostream << "Throne"; break;
		case BATTLESHIP: _ostream << "Battleship"; break;
		case POINTS: _ostream << "Points"; break;
		case GO: _ostream << "Go"; break;
		case STICS: _ostream << "Stics"; break;
		case CORNERS: _ostream << "Corners"; break;
	}
	return _ostream;
}




