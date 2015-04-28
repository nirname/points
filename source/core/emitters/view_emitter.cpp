#include "view_emitter.hpp"
#include "size_emitter.hpp"
#include "point_emitter.hpp"

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
