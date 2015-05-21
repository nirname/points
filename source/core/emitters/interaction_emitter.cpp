#include "interaction_emitter.hpp"

std::ostream & operator << (std::ostream & _ostream, const INTERACTION & interaction) {
	switch(interaction) {
		case NO_INTERACTION:      _ostream << "no interaction"; break;
		case PUSH_INTERACTION:    _ostream << "push"; break;
		case PULL_INTERACTION:    _ostream << "pull"; break;
		case JOIN_INTERACTION:    _ostream << "join"; break;
		case SLAP_INTERACTION:    _ostream << "slap"; break;
		case DESTROY_INTERACTION: _ostream << "destroy"; break;
		case DIE_INTERACTION:     _ostream << "die"; break;
		default:                  _ostream << "unknown interaction";
	}
	return _ostream;
}
