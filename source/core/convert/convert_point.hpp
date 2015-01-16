#pragma once

#include "yaml.hpp"
#include "point.hpp"

namespace YAML {

	template<>
	struct convert<Point> {

		static Node encode(const Point & point) {
			Node node;
			node.push_back(point.column);
			node.push_back(point.row);
			return node;
		}

		static bool decode(const Node & node, Point & point) {
			try {
				if(node.IsSequence() && node[0] && node[1]) {
					point = Point(node[0].as<int>(), node[1].as<int>());
				} else if (node.IsMap() && node["column"] && node["row"]) {
					point = Point(node["column"].as<int>(), node["row"].as<int>());
				} else {
					return false;
				}
			} catch(YAML::TypedBadConversion<int> & exception) {
				return false;
			}
			return true;
		}

	};

}
