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
						key = iterator->first.as<Key>();
					}
					catch(YAML::TypedBadConversion<std::string()> & exception) {
						continue;
					}
					std::cout << "to load: " << iterator->second.as<Entity>() << std::endl;

					Entity * entity = new Entity;
					*entity = iterator->second.as<Entity>();
					std::cout << "to load ptr: " << *entity << std::endl;

					//entity = manager.insert(key, entity);
					//entity = manager.insert(key, entity);
					//if(entity != NULL) {
						//try {
							//*entity = iterator->second.as<Entity>();
						//} catch(YAML::TypedBadConversion<Entity> & exception) {
							//std::cout << "\n    entity wrong value" << std::endl;
							//continue;
						//}
					//}
					/*else {
						manager.remove(key);
					}*/

						/*if(has(_name)) {
							return NULL;
						} else {
							TypePointer instance = NULL;
							try {
								instance = build();
							} catch (...) {
								std::cout << "Can not allocate memory for new entity" << std::endl;
								return NULL;
							}
							try {
								options >> *instance;
							} catch(const EXCEPTION & exception) {
								std::cout << exception << std::endl;
								delete instance;
								return NULL;
							} catch(...) {
								std::cout << "An a error occured while creating entity" << std::endl;
								delete instance;
								return NULL;
							}
							set(_name, instance);
							return instance;
						}*/

						/*Entity * entity = new Entity;
						*entity = iterator->second.as<Entity>;
						manager.insert(iterator->first.as<std::string>(), );*/

				}
			} else {
				std::cout << " should be a map" << std::endl;
				return false;
			}
			return true;
		}

	};

}
