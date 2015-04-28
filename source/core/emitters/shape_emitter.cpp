#include "shape_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const Shape & shape) {
	_ostream << "shape("
	<< ")";
	return _ostream;
}
