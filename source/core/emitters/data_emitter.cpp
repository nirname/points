#include "data_emitter.hpp"
#include "point_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const Data & data) {
	_ostream << "data(";
	_ostream << "[" << std::endl;
	for(typename Data::ConstObjectsIterator o = data.objects.begin(); o != data.objects.end(); ++o) {
		_ostream << "      " << o->first << ": " << o->second << std::endl;
	}
	_ostream << "]";
	_ostream << ")";
	return _ostream;
}
