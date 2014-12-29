#pragma once

#include <cstddef> // NULL pointer
#include <map>

template<typename Key, typename Entity> class Manager {

	public:

		typedef std::map<Key, Entity *> Entities;
		typedef typename Entities::iterator Iterator;

		Entities entities;

		Manager();
		~Manager();

		inline bool contain(const Key & _key) const;
		inline bool contain(const Key & _key, typename Entities::iterator & entity_iterator) const;

		Entity * add(const Key & _key);
		Entity * insert(const Key & _key, Entity * _entity);

		Entity * get(const Key & _key);
		Entity * operator[] (const Key & _key);

		void remove(const Key & _key);
		void clear();

		Iterator begin();
		Iterator end();

	private:

		inline Entity * create(const Key & _key);
		inline Entity * set(const Key & _key, Entity * _entity);

};

template<typename Key, typename Entity>
Manager<Key, Entity>::Manager() {}

template<typename Key, typename Entity>
Manager<Key, Entity>::~Manager() {
	clear();
}

/// Checks whether manager contains an entity or not
//
template<typename Key, typename Entity>
inline bool Manager<Key, Entity>::contain(const Key & _key) const {
	return entities.find(_key) != entities.end();
}

/// Checks whether manager contains an entity or not
//
template<typename Key, typename Entity>
inline bool Manager<Key, Entity>::contain(const Key & _key, typename Entities::iterator & entity_iterator) const {
	entity_iterator = entities.find(_key);
	return entity_iterator != entities.end();
}

/// Creates new object by name
//
template<typename Key, typename Entity>
Entity * Manager<Key, Entity>::add(const Key & _key) {
	return (contain(_key))? NULL : create(_key);
}

template<typename Key, typename Entity>
Entity * Manager<Key, Entity>::insert(const Key & _key, Entity * _entity) {
	return (contain(_key))? NULL : set(_key, _entity);
}

/// Get object without creating an extra object
//
template<typename Key, typename Entity>
Entity * Manager<Key, Entity>::get(const Key & _key) {
	typename Entities::iterator entity_iterator = entities.end();
	return (contain(_key, entity_iterator))? entity_iterator->second : NULL;
}

/// Does the same as 'get' does
//
template<typename Key, typename Entity>
Entity * Manager<Key, Entity>::operator[] (const Key & _key) {
	return get(_key);
}

/// Erases entity by key
//
template<typename Key, typename Entity>
void Manager<Key, Entity>::remove(const Key & _key) {
	typename Entities::iterator entity_iterator = entities.end();
	if(contain(_key, entity_iterator)) {
		delete entity_iterator->second;
		entities.erase(entity_iterator);
	}
}

template<typename Key, typename Entity>
void Manager<Key, Entity>::clear() {
	for(typename Entities::iterator i = entities.begin(); i != entities.end(); ++i) {
		delete i->second;
	}
	entities.clear();
}

template<typename Key, typename Entity>
typename Manager<Key, Entity>::Iterator Manager<Key, Entity>::begin() {
	return entities.begin();
}

template<typename Key, typename Entity>
typename Manager<Key, Entity>::Iterator Manager<Key, Entity>::end() {
	return entities.end();
}

/** Private ***/

/// Emplace a new instance of an entity
//
template<typename Key, typename Entity>
inline Entity * Manager<Key, Entity>::create(const Key & _key) {
	return entities[_key] = new Entity();
}

/// Emplace an existing instance of an entity
//
template<typename Key, typename Entity>
inline Entity * Manager<Key, Entity>::set(const Key & _key, Entity * _entity) {
	return entities[_key] = _entity;
}
