#pragma once

#include "object.hpp"

namespace YAML {

	template<>
	struct convert<Object> {
		static Node encode(const Object & object) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, Object & object) {
			return false;
		}
	};

}
