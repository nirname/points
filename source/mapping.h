#pragma once

template<typename Type> class Mapping {

	public:

		typedef std::string KeyType;
		typedef Type * TypePointer;

		typedef std::map<KeyType, TypePointer> Container;
		typedef typename Container::iterator Iterator;

	private:

		Container container;

	public:

		Mapping() {}

		void clear() {
			for(typename Container::iterator i = container.begin(); i != container.end(); ++i) {
				delete i->second;
			}
			container.clear();
		}

		~Mapping() {
			clear();
		}

	private:

		inline TypePointer build() {
			return new Type();
		}

		// Retrive an entry from container or create a new one
		inline TypePointer fetch(const KeyType & _name) {
			return container[_name];
		}

		// Creates new object by name
		inline TypePointer set(const KeyType & _name) {
			TypePointer result = new Type();
			container[_name] = result;
			return result;
		}

		inline TypePointer set(const KeyType & _name, TypePointer _pointer) {
			container[_name] = _pointer;
			return _pointer;
		}

	public:

		// Checkes if container contains an ojbect by name
		inline bool has(const KeyType & _name) {
			return container.find(_name) != container.end();
		}

		// Get object without creating an extra object
		TypePointer get(const KeyType & _name) {
			return (has(_name))? fetch(_name) : NULL;
		}

		// Returns pointer if successed
		// Otherwise returns NULL

		TypePointer add(const KeyType & _name) {
			return (has(_name))? NULL : set(_name);
		}

		TypePointer add(const KeyType & _name, TypePointer _pointer) {
			if(has(_name)) {
				delete _pointer;
				return NULL;
			} else {
				set(_name, _pointer);
				return _pointer;
			}
		}

		TypePointer add(const KeyType & _name, const YAML::Node & options) {
			if(has(_name)) {
				return NULL;
			} else {
				// TODO catch exceptions here
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
			}
		}

		// Adds or gets
		TypePointer use(const KeyType & _name) {
			return (has(_name))? fetch(_name) : set(_name);
		}

		// Does the same as 'get' does
		TypePointer operator[] (const KeyType & _name) {
			return get(_name);
		}

		// Erases element by name
		void remove(const KeyType & _name) {
			if(has(_name)) {
				delete fetch(_name);
				container.erase(_name);
			}
		}

		Iterator begin() {
			return container.begin();
		}

		Iterator end() {
			return container.end();
		}

		void print(std::ostream & _ostream = std::cout) {
			if(!container.empty()) {
				for(Iterator iterator = container.begin(); iterator != container.end(); ++iterator) {
					_ostream << iterator->first << " (" << iterator->second << "): " << *iterator->second << std::endl;
				}
			} else {
				_ostream << "is empty" << std::endl;
			}
		}

}; // template Mapping

template<typename Type> std::ostream & operator << (std::ostream & _ostream, Mapping<Type> & mapping) {
	mapping.print(_ostream);
	return _ostream;
}

template<typename Type> void operator >> (const YAML::const_iterator & iterator, Mapping<Type> & mapping) {
	try {
		mapping.add(iterator->first.as<std::string>(), iterator->second);
	}
	catch(YAML::TypedBadConversion<std::string()> & exception) {
		std::cout << "Can't upload entity" << std::endl;
	}
}
