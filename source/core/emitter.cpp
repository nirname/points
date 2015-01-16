#include "emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const SCREENSAVER_KIND & screensaver_kind) {
	switch(screensaver_kind) {
		case NO_SCREENSAVER:                   _ostream << "no";             break;
		case LIFE_SCREENSAVER:                 _ostream << "life";           break;
		case QUEENS_SCREENSAVER:               _ostream << "queens";         break;
		case GEOGRAPHIC_EARTH_MAP_SCREENSAVER: _ostream << "geographic map"; break;
		case DAY_NIGHT_EARTH_MAP_SCREENSAVER:  _ostream << "day nigth map";  break;
		case POLITICAL_EARTH_MAP_SCREENSAVER:  _ostream << "political map";  break;
		case TURTLE_SCREENSAVER:               _ostream << "turtle";         break;
		case EQUALIZER_SCREENSAVER:            _ostream << "equalizer";      break;
		case TIMER_SCREENSAVER:                _ostream << "timer";          break;
		case RANDOM_SCREENSAVER:               _ostream << "random";         break;
		default: {
			_ostream << "[ ";
				for(SCREENSAVER_KIND k = LIFE_SCREENSAVER; k <= TIMER_SCREENSAVER; k++) {
					if(screensaver_kind & k) {
						_ostream << k << " ";
					}
				}
			_ostream << "]";
			break;
		}
	}
	return _ostream;
}

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

std::ostream & operator << (std::ostream & _ostream, const APPLICATION_MODE & application_mode) {
	switch(application_mode) {
		case LOADING_MODE:     _ostream << "loading mode";     break;
		case FOREWORD_MODE:    _ostream << "foreword mode";    break;
		case MENU_MODE:        _ostream << "menu mode";        break;
		case SCREENSAVER_MODE: _ostream << "screensaver mode"; break;
		case COUNTDOWN_MODE:   _ostream << "countdown mode";   break;
		case GAMEPLAY_MODE:    _ostream << "gameplay mode";    break;
		case INFORMATION_MODE: _ostream << "information mode"; break;
		case AFTERWORD_MODE:   _ostream << "afterword mode";   break;
	}
	return _ostream;
}

std::ostream & operator << (std::ostream & _ostream, const Color & color) {
	_ostream << "color("
		<< color.red << ", "
		<< color.green << ", "
		<< color.blue
	<< ")";
	return _ostream;
}

std::ostream & operator << (std::ostream & _ostream, const AspectRatio & aspect_ratio) {
	_ostream << "aspect_ratio("
		<< aspect_ratio.width << ", "
		<< aspect_ratio.height
	<< ")";
	return _ostream;
}

std::ostream & operator << (std::ostream & _ostream, const Size & size) {
	_ostream << "size("
		<< size.width << ", "
		<< size.height
	<< ")";
	return _ostream;
}

std::ostream & operator << (std::ostream & _ostream, const Field & field) {
	_ostream << "field("
		<< "size: " << field.size
	<< ")";
	return _ostream;
}

std::ostream & operator << (std::ostream & _ostream, const Object & object) {
	_ostream << "object("
	<< ")";
	return _ostream;
}

std::ostream & operator << (std::ostream & _ostream, const ObjectKind & object_kind) {
	_ostream << "object_kind("
	<< ")";
	return _ostream;
}

std::ostream & operator << (std::ostream & _ostream, const View & view) {
	_ostream << "view("
		<< "size: " << view.size << ", "
		<< "field: " << view.field << ", "
		<< "background_color: " << view.background_color << ", "
		<< "field_color: " << view.field_color << ", "
		<< "cells_color: " << view.cells_color << ", "
		<< "grid_color: " << view.grid_color << ", "
		<< "border_color: " << view.border_color << ", "
		<< "position: " << view.position << ", "
		<< "direction: " << view.direction << ", "
		<< "offset: " << view.offset
	<< ")";
	return _ostream;
}

std::ostream & operator << (std::ostream & _ostream, const Point & point) {
	_ostream << "point("
		<< point.column << ", "
		<< point.row
	<< ")";
	return _ostream;
}

std::ostream & operator << (std::ostream & _ostream, const Shape & shape) {
	_ostream << "shape("
	<< ")";
	return _ostream;
}
