#pragma once

#include "yaml.hpp"
#include "interaction_type.hpp"

#include "library.hpp"
#include "emitters/interaction_type_emitter.hpp"

namespace YAML {

	template<>
	struct convert<INTERACTION_TYPE> {

		static Node encode(const INTERACTION_TYPE & interaction) {
			Node node;
			node = to_string(interaction);
			return node;
		}

		static bool decode(const Node & node, INTERACTION_TYPE & interaction) {
			try {
				if(node.IsScalar()) {
					std::string interaction_name = node.as<std::string>();
					for(INTERACTION_TYPE i = NO_INTERACTION; i <= DIE_INTERACTION; i++) {
						if(interaction_name == to_string(i)) {
							interaction = i;
							return true;
						}
					}
					return false;
				} else {
					return false;
				}
			} catch(YAML::TypedBadConversion<std::string()> & exception) {
				return false;
			}
			return true;
		}

	};

}
