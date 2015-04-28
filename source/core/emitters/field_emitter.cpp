#include "field_emitter.hpp"
#include "size_emitter.hpp"
#include "data_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const Field & field) {
	_ostream << "field("
		<< "size: " << field.size << ", "
		<< "data: " << field.data
	<< ")";
	return _ostream;
}
