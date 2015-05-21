#pragma once

#include "yaml.hpp"
#include "interaction.hpp"

#include "library.hpp"
#include "emitters/interaction_emitter.hpp"

namespace YAML {

	template<>
	struct convert<INTERACTION> {

		static Node encode(const INTERACTION & interaction) {
			Node node;
			node = to_string(interaction);
			return node;
		}

		static bool decode(const Node & node, INTERACTION & interaction) {
			try {
				if(node.IsScalar()) {
					std::string interaction_name = node.as<std::string>();
					for(INTERACTION i = NO_INTERACTION; i <= DIE_INTERACTION; i++) {
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
