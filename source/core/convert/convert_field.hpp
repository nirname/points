#pragma once

#include "yaml.hpp"
#include "field.hpp"

namespace YAML {

	template<>
	struct convert<Field> {
		static Node encode(const Field & field) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, Field & field) {
			return false;
		}
	};

}
