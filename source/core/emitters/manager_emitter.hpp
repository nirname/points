#pragma once

#include <ostream>
#include "manager.hpp"

template<typename Key, typename Entity>
std::ostream & operator << (std::ostream & _ostream, const Manager<Key, Entity> & manager) {
	if(!manager.empty()) {
		for(typename Manager<Key, Entity>::ConstEntityIterator i = manager.entities.begin(); i != manager.entities.end(); ++i) {
			//_ostream << i->first << " (" << i->second << "): " << *i->second << std::endl;
			_ostream << "    " << i->first << "#" << i->second << ": " << *i->second << std::endl;
			//_ostream << i->first << "#" << i->second << " " << std::ends;
		}
		for(typename Manager<Key, Entity>::ConstItemIterator i = manager.items.begin(); i != manager.items.end(); ++i) {
			_ostream << "    " << "#" << *i << ": " << **i << std::endl;
		}
	} else {
		_ostream << "    is empty";
	}
	return _ostream;
}
