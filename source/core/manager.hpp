#pragma once

#include <cstddef> // NULL pointer
#include <map>
#include <set>
#include <iostream>

template<typename Key, typename Entity> class Manager {

	public: // Types and members

		class CopyDepracationException {};

		typedef std::map<Key, Entity *> Entities;
		typedef typename Entities::iterator EntityIterator;
		typedef typename Entities::const_iterator ConstEntityIterator;

		typedef std::set<Entity *> Items;
		typedef typename Items::iterator ItemIterator;
		typedef typename Items::const_iterator ItemConstIterator;

		Entities entities;
		Items items;

		Manager();
		Manager(const Manager &);
		Manager & operator = (const Manager & arg);
		~Manager();

		inline bool contain(const Key & _key);
		inline bool contain(const Key & _key, EntityIterator & entity_iterator);
		inline bool contain(Entity * _entity);
		inline bool contain(Entity * _entity, ItemIterator & item_iterator);

		Entity * add(const Key & _key);
		Entity * add();

		Entity * insert(const Key & _key, Entity * _entity);
		Entity * insert(Entity * _entity);

		Entity * get(const Key & _key);
		Entity * get(Entity * _entity);

		Entity * operator[] (const Key & _key);
		Entity * operator[] (Entity * _key);

		void remove(const Key & _key);
		void remove(Entity *);

		void clear();


		// TODO: remove iterators, make a callback instead
		EntityIterator entities_begin();
		EntityIterator entities_end();

		EntityIterator items_begin();
		EntityIterator items_end();

		inline bool empty() const;

		void each(void(*f)(Entity *));

	private:

		inline Entity * create(const Key & _key);
		inline Entity * emplace(const Key & _key, Entity * _entity);

};

template<typename Key, typename Entity>
Manager<Key, Entity>::Manager() {}

template<typename Key, typename Entity>
Manager<Key, Entity>::Manager(const Manager & manager) {
	throw CopyDepracationException();
}

template<typename Key, typename Entity>
Manager<Key, Entity> & Manager<Key, Entity>::operator =(const Manager<Key, Entity> & manager) {
	throw CopyDepracationException();
}

template<typename Key, typename Entity>
Manager<Key, Entity>::~Manager() {
	clear();
}

/// Checks whether manager contains an entity or not
//
template<typename Key, typename Entity>
inline bool Manager<Key, Entity>::contain(const Key & _key) {
	return entities.find(_key) != entities.end();
}

/// Checks whether manager contains an entity or not
//
template<typename Key, typename Entity>
inline bool Manager<Key, Entity>::contain(const Key & _key, EntityIterator & entity_iterator) {
	entity_iterator = entities.find(_key);
	return entity_iterator != entities.end();
}

/// Checks whether manager contains an entity or not
//
template<typename Key, typename Entity>
inline bool Manager<Key, Entity>::contain(Entity * _entity) {
	return items.find(_entity) != items.end();
}

/// Checks whether manager contains an entity or not
//
template<typename Key, typename Entity>
inline bool Manager<Key, Entity>::contain(Entity * _entity, ItemIterator & item_iterator) {
	item_iterator = items.find(_entity);
	return item_iterator != items.end();
}

/// Creates new object by name
//
/// If an object with the same name already exists than NULL is returned.
/// If an error occures than NULL is returned
///
template<typename Key, typename Entity>
Entity * Manager<Key, Entity>::add(const Key & _key) {
	return (contain(_key))? NULL : create(_key);
}

template<typename Key, typename Entity>
Entity * Manager<Key, Entity>::add() {
	return create();
}

/// Inserts already created named object by it's pointer
//
/// If an object with the same name already exists than NULL is returned.
/// If an error occures than NULL is returned
///
template<typename Key, typename Entity>
Entity * Manager<Key, Entity>::insert(const Key & _key, Entity * _entity) {
	return (contain(_key))? NULL : emplace(_key, _entity);
}

/// Inserts already created unnamed object by it's pointer
//
/// If an object with the same pointer already exists than NULL is returned.
/// If an error occures than NULL is returned
///
template<typename Key, typename Entity>
Entity * Manager<Key, Entity>::insert(Entity * _entity) {
	return (contain(_entity))? NULL : emplace(_entity);
}

/// Get object without creating an extra object
//
template<typename Key, typename Entity>
Entity * Manager<Key, Entity>::get(const Key & _key) {
	EntityIterator entity_iterator = entities.end();
	return (contain(_key, entity_iterator))? entity_iterator->second : NULL;
}

/// Get object without creating an extra object
//
template<typename Key, typename Entity>
Entity * Manager<Key, Entity>::get(Entity * _entity) {
	ItemIterator item_iterator = items.end();
	return (contain(_entity, item_iterator))? *item_iterator : NULL;
}

/// Does the same as 'get' does
//
template<typename Key, typename Entity>
Entity * Manager<Key, Entity>::operator[] (const Key & _key) {
	return get(_key);
}

/// Does the same as 'get' does
//
template<typename Key, typename Entity>
Entity * Manager<Key, Entity>::operator[] (Entity * _entity) {
	return get(_entity);
}

/// Erases entity by key
//
template<typename Key, typename Entity>
void Manager<Key, Entity>::remove(const Key & _key) {
	EntityIterator entity_iterator = entities.end();
	if(contain(_key, entity_iterator)) {
		delete entity_iterator->second;
		entities.erase(entity_iterator);
	}
}

template<typename Key, typename Entity>
void Manager<Key, Entity>::remove(Entity * _entity) {
	ItemIterator item_iterator = items.end();
	if(contain(_entity, item_iterator)) {
		delete *item_iterator;
		items.erase(item_iterator);
	}
}

template<typename Key, typename Entity>
void Manager<Key, Entity>::clear() {
	for(EntityIterator i = entities.begin(); i != entities.end(); ++i) {
		delete i->second;
	}
	for(ItemIterator i = items.begin(); i != items.end(); ++i) {
		delete *i;
	}
	items.clear();
	entities.clear();
}

template<typename Key, typename Entity>
typename Manager<Key, Entity>::EntityIterator Manager<Key, Entity>::entities_begin() {
	return entities.begin();
}

template<typename Key, typename Entity>
typename Manager<Key, Entity>::EntityIterator Manager<Key, Entity>::entities_end() {
	return entities.end();
}

template<typename Key, typename Entity>
inline bool Manager<Key, Entity>::empty() const {
	return entities.empty() && items.empty();
}

/** Private ***/


/// Emplace a new instance of an entity
//
template<typename Key, typename Entity>
inline Entity * Manager<Key, Entity>::create(const Key & _key) {
	Entity * new_entity = new Entity();
	return emplace(_key, new_entity);
}

/// Emplace an existing instance of an entity
//
template<typename Key, typename Entity>
inline Entity * Manager<Key, Entity>::emplace(const Key & _key, Entity * _entity) {
	return entities[_key] = _entity;
	/*std::cout << "emplacing: " << _entity << ": " << *_entity << std::endl;
	entities.insert(std::pair<Key, Entity *>(_key, _entity) );
	return _entity;*/
}
