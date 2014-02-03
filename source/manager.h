#pragma once

template<typename Entity, typename Key> class Manager {

	private:

		// TODO: make container type a template parameter

		typedef std::map<Key, Entity *> NamesInfo;
		typedef std::map<Entity *, Key> EntitiesInfo;

		NamesInfo names;
		EntitiesInfo entities;

	public:

		Manager() {}

		~Manager() {
			//clear();
		}

		bool contain(const Key & _name) {
			return names.find(_name) != names.end();
		}

		bool contain(const Entity * _entity) {
			return entities.find(_entity) != entities.end();
		}

		// Named entities
		Entity * add(const Key & _name) {}
		Entity * add(const Key & _name, Entity * _entity) {}
		Entity * add(const Key & _name, const YAML::Node & _options) {}
		// Unnamed entities
		Entity * add(Entity * _entity) {}
		Entity * add(const YAML::Node & _options) {}

		void remove(const Key & _name) {
			if(contain(_name)) {
				Entity * _entity = names[_name];
				entities.erase(_entity);
				names.erase(_name);
				delete _entity;
			}
		}
		void remove(Entity * _entity) {
			if(contain(_entity)) {
				//delete entities[]
			}
		}

		void clear() {
			for(typename EntitiesInfo::iterator
			i = entities.begin();
			i != entities.end();
			++i) {
				delete (i->first);
			}
		};
		void print();

};

/*template<typename Entity, typename Key>
void Manager<Entity, Key>::clear{
}*/

//template<typename Entity, typename Key> Manager
