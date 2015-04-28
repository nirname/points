#include "action_kind_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const ACTION_KIND & action_kind) {
	switch(action_kind) {
		case NO_ACTION:      _ostream << "no action"; break;
		case MOVE_ACTION:    _ostream << "move";      break;
		case GO_TO_ACTION:   _ostream << "go to";     break;
		case ROTATE_ACTION:  _ostream << "turn";      break;
		case REFLECT_ACTION: _ostream << "reflect";   break;
	}
	return _ostream;
};
