#pragma once

#include "yaml.hpp"
#include "aspect_ratio.hpp"

namespace YAML {

	template<>
	struct convert<ACTION_KIND> {

		static Node encode(const ACTION_KIND & action_kind) {
			Node node;
			throw "not implemented";
			return node;
		}

		static bool decode(const Node & node, ACTION_KIND & action_kind) {
			try {
				if(node.IsScalar()) {
					std::string action_kind_name = node.as<std::string>();
					if(action_kind_name == "no action") {
					} else
					return false;
				}
			} catch(...) {}
			return true;
		}

	};

}
