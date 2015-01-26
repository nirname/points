#pragma once

#include <ostream>

#include "screensaver.hpp"
#include "color.hpp"
#include "game.hpp"
#include "application.hpp"
#include "screen.hpp"
#include "size.hpp"
#include "manager.hpp"
#include "data.hpp"
#include "field.hpp"
#include "object.hpp"
#include "object_kind.hpp"
#include "view.hpp"
#include "shape.hpp"
#include "point.hpp"

std::ostream & operator << (std::ostream & _ostream, const SCREENSAVER_KIND & screensaver_kind);
std::ostream & operator << (std::ostream & _ostream, const APPLICATION_MODE & application_mode);
std::ostream & operator << (std::ostream & _ostream, const GAME_KIND & game_kind);
std::ostream & operator << (std::ostream & _ostream, const Color & color);
std::ostream & operator << (std::ostream & _ostream, const AspectRatio & aspect_ratio);
std::ostream & operator << (std::ostream & _ostream, const Point & point);
std::ostream & operator << (std::ostream & _ostream, const Size & size);
std::ostream & operator << (std::ostream & _ostream, const Field & field);
std::ostream & operator << (std::ostream & _ostream, const Object & object);
std::ostream & operator << (std::ostream & _ostream, const ObjectKind & object_kind);
std::ostream & operator << (std::ostream & _ostream, const View & view);
std::ostream & operator << (std::ostream & _ostream, const Shape & shape);
std::ostream & operator << (std::ostream & _ostream, const Data & data);

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
