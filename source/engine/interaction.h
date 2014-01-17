#pragma once

namespace engine {

	INTERACTION_TYPE get_interaction_type(std::string const & interaction_type_name) {
		if(interaction_type_name == "push") return PUSH_INTERACTION;
		if(interaction_type_name == "pull") return PULL_INTERACTION;
		if(interaction_type_name == "destroy") return DESTROY_INTERACTION;
		if(interaction_type_name == "create") return CREATE_INTERACTION;
		return NO_INTERACTION;
	}

	std::ostream & operator << (std::ostream & _ostream, const INTERACTION_TYPE & interaction) {
		std::string interaction_name;
		switch(interaction) {
			case NO_INTERACTION:      interaction_name = "no interaction"; break;
			case PUSH_INTERACTION:    interaction_name = "push";           break;
			case PULL_INTERACTION:    interaction_name = "pull";           break;
			case DESTROY_INTERACTION: interaction_name = "destroy";        break;
			case CREATE_INTERACTION:  interaction_name = "create";         break;
		}
		_ostream << interaction_name;
		return _ostream;
	}

}
