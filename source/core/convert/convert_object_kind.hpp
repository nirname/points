#pragma once

#include "yaml.hpp"
#include "object_kind.hpp"

namespace YAML {

	template<>
	struct convert<ObjectKind> {
		static Node encode(const ObjectKind & object_kind) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, ObjectKind & object_kind) {
			if(node.IsNull()) {
				// all values are default
			} else if(node.IsMap()) {
			}
			/*switch(node.Type()) {
				case YAML::NodeType::Undefined: std::cout << "Undefined" << std::endl; break;
				case YAML::NodeType::Null: std::cout << "Null" << std::endl; break;
				case YAML::NodeType::Scalar: std::cout << "Scalar" << std::endl; break;
				case YAML::NodeType::Sequence: std::cout << "Sequence" << std::endl; break;
				case YAML::NodeType::Map: std::cout << "Map" << std::endl; break;
				default: std::cout << "something strange" << std::endl; break;
			}*/
			return true;
		}
	};

}
