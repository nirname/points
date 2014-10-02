#pragma once

#include <cstddef> // NULL pointer
#include <map>

template<typename Key, typename Entity> struct Manager {

		typedef std::map<Key, Entity *> Entities;
		Entities entities;

		Manager() {
		}

		~Manager() {
			clear();
		}

		void clear() {
			for(typename Entities::iterator i = entities.begin(); i != entities.end(); ++i) {
				delete i->second;
			}
			entities.clear();
		}

		/// Creates new instance of Entity
		//
		Entity * build() {
			return new Entity();
		}

		/// Retrive an entry from container or create an empty record
		//
		Entity * fetch(const Key & _key) {
			return entities[_key];
		}

		/// Checks whether manager contains an entity or not
		//
		bool contain(const Key & _key) {
			return entities.find(_key) != entities.end();
		}

		/// Checks whether manager contains an entity or not
		//
		bool contain(const Key & _key, typename Entities::iterator & entity_iterator) {
			entity_iterator = entities.find(_key);
			return entity_iterator != entities.end();
		}

		/// Emplace a new instance of an entity
		//
		Entity * set(const Key & _key) {
			return entities[_key] = build();
		}

		/// Emplace an existing instance of an entity
		//
		Entity * set(const Key & _key, Entity * _entity) {
			return entities[_key] = _entity;
		}

		/// Creates new object by name
		//
		Entity * add(const Key & _key) {
			return (contain(_key))? NULL : set(_key);
		}

		/// Get object without creating an extra object
		//
		Entity * get(const Key & _key) {
			typename Entities::iterator entity_iterator = entities.end();
			return (contain(_key, entity_iterator))? entity_iterator->second : NULL;
		}

		// Does the same as 'get' does
		Entity * operator[] (const Key & _key) {
			return get(_key);
		}

		/// Erases entity by key
		//
		void remove(const Key & _key) {
			typename Entities::iterator entity_iterator = entities.end();
			if(contain(_key, entity_iterator)) {
				delete entity_iterator->second;
				entities.erase(entity_iterator);
			}
		}

};
