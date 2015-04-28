#include "object_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const Object & object) {
	_ostream << "object("
		<< "kind: " << object.kind
	<< ")";
	return _ostream;
}
