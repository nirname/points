#pragma once

#include "aspect_ratio.hpp"

namespace YAML {

	template<>
	struct convert<AspectRatio> {

		static Node encode(const AspectRatio & aspect_ratio) {
			Node node;
			node.push_back(aspect_ratio.width);
			node.push_back(aspect_ratio.height);
			return node;
		}

		static bool decode(const Node & node, AspectRatio & aspect_ratio) {
			try {
				if(node.IsSequence() && node[0] && node[1]) {
					aspect_ratio = AspectRatio(node[0].as<unsigned int>(), node[1].as<unsigned int>());
				} else if (node.IsMap() && node["width"] && node["height"]) {
					aspect_ratio = AspectRatio(
						node["width"].as<unsigned int>(),
						node["height"].as<unsigned int>()
					);
				} else {
					return false;
				}
			} catch(...) {}
			return true;
		}

	};

}
