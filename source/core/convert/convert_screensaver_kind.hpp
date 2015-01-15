#pragma once

#include "yaml.hpp"
#include "screensaver_kind.hpp"

#include "library.hpp"
#include "emitter.hpp"

namespace YAML {

	template<>
	struct convert<SCREENSAVER_KIND> {
		static Node encode(const SCREENSAVER_KIND & screensaver_kind) {
			Node node;
			if(screensaver_kind == RANDOM_SCREENSAVER || screensaver_kind == NO_SCREENSAVER) {
				node = to_string(screensaver_kind);
			} else {
				for(SCREENSAVER_KIND s = LIFE_SCREENSAVER; s <= TIMER_SCREENSAVER; s++) {
					if(screensaver_kind & s) {
						node.push_back(to_string(s));
					}
				}
			}
			return node;
		}

		static bool decode(const Node & node, SCREENSAVER_KIND & screensaver_kind) {
			screensaver_kind = NO_SCREENSAVER;
			std::string screensaver_name;
			if(node.IsScalar()) {
				screensaver_name = node.as<std::string>();
				if(screensaver_name == "random") {
					screensaver_kind = RANDOM_SCREENSAVER;
				} else {
					for(SCREENSAVER_KIND s = LIFE_SCREENSAVER; s <= TIMER_SCREENSAVER; s++) {
						if(screensaver_name == to_string(s)) {
							screensaver_kind = SCREENSAVER_KIND(screensaver_kind | s);
						}
					}
				}
			} else if (node.IsSequence()) {
				for(unsigned int i = 0; i < node.size(); i++) {
					screensaver_name = node[0].as<std::string>();
					for(SCREENSAVER_KIND s = LIFE_SCREENSAVER; s <= TIMER_SCREENSAVER; s++) {
						if(screensaver_name == to_string(s)) {
							screensaver_kind = SCREENSAVER_KIND(screensaver_kind | s);
						}
					}
				}
			} else {
				return false;
			}
			return true;
		}

	};

}
