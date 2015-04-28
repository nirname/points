#include "game_kind_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const GAME_KIND & game_kind) {
	switch(game_kind) {
		case NO_GAME:       _ostream << "no game"; break;
		case SNAKE:         _ostream << "snake"; break;
		case SOKOBAN:       _ostream << "sokoban"; break;
		case ATOMIX:        _ostream << "atomix"; break;
		case RUSH_HOUR:     _ostream << "rush hour"; break;
		case LIGHTS:        _ostream << "lights"; break;
		case TETRIS:        _ostream << "tetris"; break;
		case ROBOTS:        _ostream << "robots"; break;
		case LABYRINTH:     _ostream << "labyrinth"; break;
		case SWAP:          _ostream << "swap"; break;
		case POLYMINO:      _ostream << "polymino"; break;
		case BACKGROUND:    _ostream << "background"; break;
		case LINES:         _ostream << "lines"; break;
		case NETWALK:       _ostream << "netwalk"; break;
		case MOWER:         _ostream << "mower"; break;
		case MASYU:         _ostream << "masyu"; break;
		case RINGS:         _ostream << "rings"; break;
		case BOMBERMAN:     _ostream << "bomberman"; break;
		case PACMAN:        _ostream << "pacman"; break;
		case GAME1024:      _ostream << "1024"; break;
		case GAME1010:      _ostream << "10*10!"; break;
		case REVERSI:       _ostream << "reversi"; break;
		case GOMOKU:        _ostream << "gomoku"; break;
		case FOUR_IN_A_ROW: _ostream << "4 in a row"; break;
		case TRHONE:        _ostream << "throne"; break;
		case BATTLESHIP:    _ostream << "battleship"; break;
		//case POINTS:        _ostream << "points"; break;
		case GO:            _ostream << "go"; break;
		case STICS:         _ostream << "stics"; break;
		case CORNERS:       _ostream << "corners"; break;
		default:            _ostream << "unknown";
	}
	return _ostream;
}
