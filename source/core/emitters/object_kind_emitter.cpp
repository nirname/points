#include "object_kind_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const ObjectKind & object_kind) {
	_ostream << "object_kind(" << &object_kind << ")";
	return _ostream;
}
