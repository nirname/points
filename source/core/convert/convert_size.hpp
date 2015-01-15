#pragma once

#include "size.hpp"

namespace YAML {

	template<>
	struct convert<Size> {

		static Node encode(const Size & size) {
			Node node;
			node.push_back(size.width);
			node.push_back(size.height);
			return node;
		}

		static bool decode(const Node & node, Size & size) {
			if(node.IsSequence() && node[0] && node[1]) {
				size = Size(node[0].as<unsigned int>(), node[1].as<unsigned int>());
			} else if (node.IsMap() && node["width"] && node["height"]) {
				size = Size(node[0].as<unsigned int>(), node[1].as<unsigned int>());
			} else {
				return false;
			}
			return true;
		}

	};

}
