#include "size_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const Size & size) {
	_ostream << "size("
		<< size.width << ", "
		<< size.height
	<< ")";
	return _ostream;
}
