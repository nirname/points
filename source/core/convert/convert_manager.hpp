#pragma once

#include "manager.hpp"

namespace YAML {

	template<class Key, class Entity>
	struct convert< Manager<Key, Entity> > {

		static Node encode(const Manager<Key, Entity> & manager) {
			Node node;
			return node;
		}

		static bool decode(const Node & node, Manager<Key, Entity> & manager) {
			if(node.IsMap()) {
				Key key;
				for(YAML::const_iterator iterator = node.begin(); iterator != node.end(); ++iterator) {
					try {
						convert<Key>().decode(iterator->first, key);
						std::cout << key << ": " << std::ends;
					}
					catch(YAML::TypedBadConversion<std::string()> & exception) {
						continue;
					}
					Entity * entity = manager.add(key);
					if(entity != NULL) {
						try {
							convert<Entity>().decode(iterator->second, *entity);
						} catch(YAML::TypedBadConversion<Entity> & exception) {
							delete entity;
							return false;
						}
					}
				}
			} else {
				std::cout << " should be a map" << std::endl;
				return false;
			}
			return true;
		}

	};

}
