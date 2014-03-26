#pragma once

enum GRID_TYPE {
	SQUARE_GRID,
	EDGE_BASED_HEXAGON_GRID,
	CORNER_BASED_HEXAGON_GRID
};

std::ostream & operator << (std::ostream & _ostream, const GRID_TYPE & _grid_type) {
	switch(_grid_type) {
		case SQUARE_GRID: _ostream << "Square"; break;
		case EDGE_BASED_HEXAGON_GRID: _ostream << "Edge-based hexagon"; break;
		case CORNER_BASED_HEXAGON_GRID: _ostream << "Corner-based hexagon"; break;
	}
	return _ostream;
}
