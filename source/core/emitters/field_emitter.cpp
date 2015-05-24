#include "field_emitter.hpp"
#include "size_emitter.hpp"
#include "data_emitter.hpp"
#include "point_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const Field & field) {
	_ostream << "field("
		<< "size: " << field.size << ", "
		<< "data: " << field.data << ", "
		<< "cells: ";
	for(CellsSet::iterator i = field.cells.begin(); i != field.cells.end(); ++i) {
		_ostream << *i;
	}
	_ostream << ")";
	return _ostream;
}
