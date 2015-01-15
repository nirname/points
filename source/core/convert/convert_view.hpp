#pragma once

#include "view.hpp"

namespace YAML {

	template<>
	struct convert<View> {
		static Node encode(const View & view) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, View & view) {
			return false;
		}
	};

}
