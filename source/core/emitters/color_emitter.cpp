#include "color_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const Color & color) {
	_ostream << "color("
		<< color.red << ", "
		<< color.green << ", "
		<< color.blue
	<< ")";
	return _ostream;
}
