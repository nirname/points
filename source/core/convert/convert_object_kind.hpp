#pragma once

#include "object_kind.hpp"

namespace YAML {

	template<>
	struct convert<ObjectKind> {
		static Node encode(const ObjectKind & object_kind) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, ObjectKind & object_kind) {
			return false;
		}
	};

}
