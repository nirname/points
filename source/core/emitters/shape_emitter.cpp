#include "shape_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const Shape & shape) {
	_ostream << "shape("
		<< "basic_shape: " << *shape.basic_shape
	<< ")";
	return _ostream;
}
