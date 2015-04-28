#include "point_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const Point & point) {
	_ostream << "point("
		<< point.column << ", "
		<< point.row
	<< ")";
	return _ostream;
}
