#pragma once

namespace engine {

	INTERACTION_TYPE get_interaction_type(std::string const & interaction_name) {
		if(interaction_name == "push")    return PUSH_INTERACTION;
		if(interaction_name == "pull")    return PULL_INTERACTION;
		if(interaction_name == "join")    return JOIN_INTERACTION;
		if(interaction_name == "slap")    return SLAP_INTERACTION;
		if(interaction_name == "destroy") return DESTROY_INTERACTION;
		if(interaction_name == "die")     return DIE_INTERACTION;
		return NO_INTERACTION;
	}

	std::ostream & operator << (std::ostream & _ostream, const INTERACTION_TYPE & interaction) {
		switch(interaction) {
			case NO_INTERACTION:      _ostream << "no interaction"; break;
			case PUSH_INTERACTION:    _ostream << "push";           break;
			case PULL_INTERACTION:    _ostream << "pull";           break;
			case JOIN_INTERACTION:    _ostream << "join";           break;
			case SLAP_INTERACTION:    _ostream << "slap";           break;
			case DESTROY_INTERACTION: _ostream << "destroy";        break;
			case DIE_INTERACTION:     _ostream << "die";            break;
		}
		return _ostream;
	}

}
