#ifndef MAPPING_H
#define MAPPING_H 1

template<typename Type> class Mapping {

	public:

		typedef Type * TypePointer;
		typedef std::map<KeyType, TypePointer> Container;
		typedef typename Container::iterator Iterator;

	private:

		Container container;

	public:

		Mapping() {}

		~Mapping() {
			for(typename Container::iterator i = container.begin(); i != container.end(); ++i) {
				delete i->second;
			}
		}

	private:

		inline TypePointer build() {
			return new Type();
		}

		// Alias for container operator []
		inline TypePointer fetch(std::string _name) {
			return container[_name];
		}

		// Creates new object by name
		inline TypePointer set(std::string _name) {
			TypePointer result = new Type();
			container[_name] = result;
			return result;
		}

		inline TypePointer set(std::string _name, TypePointer _pointer) {
			container[_name] = _pointer;
			return _pointer;
		}

	public:

		// Checkes if container contains an ojbect by name
		inline bool has(std::string _name) {
			return container.find(_name) != container.end();
		}

		// Get object without creatinga an extra object
		TypePointer get(std::string _name) {
			return (has(_name))? fetch(_name) : NULL;
		}

		// Returns pointer if successed
		// Otherwise returns NULL
		TypePointer add(std::string _name) {
			return (has(_name))? NULL : set(_name);
		}

		TypePointer add(std::string _name, TypePointer _pointer) {
			if(has(_name)) {
				delete _pointer;
				return NULL;
			} else {
				set(_name, _pointer);
				return _pointer;
			}
		}

		TypePointer add(std::string _name, const YAML::Node& options) {
			if(has(_name)) {
				return NULL;
			} else {
				TypePointer instance = build();
				options >> *instance;
				set(_name, instance);
				return instance;
			}
		}

		// Adds or gets
		TypePointer use(std::string _name) {
			return (has(_name))? fetch(_name) : set(_name);
		}

		// Does the same as 'get' does
		TypePointer operator[] (std::string _name) {
			return this->get(_name);
		}

		// Does the same action for each element
		/*void each(void (* handler)(TypePointer)) {
			for(Iterator object = container.begin(); object != container.end(); ++object) {
				handler(object->second);
			}
		}*/

		Iterator begin() {
			return container.begin();
		}

		Iterator end() {
			return container.end();
		}


		void print(std::ostream & _ostream = std::cout) {
			if(!container.empty()) {
				for(Iterator iterator = container.begin(); iterator != container.end(); ++iterator) {
					_ostream << iterator->first << ": " << iterator->second << std::endl;
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

/*void operator >> (std::string s, Mapping<typename Type> &) {
	std::cout << "HELLO!!!!!!!!!!" << std::endl;
}*/

/*template<typename T> void qqq(std::string s, Mapping<T> &) {
}

template<typename T> void operator >> (std::string s, Mapping<T> &) {
	std::cout << s << std::endl;
}*/

template<typename T> void operator >> (const YAML::const_iterator & iterator, Mapping<T> & mapping) {
	std::string entity_name = iterator->first.as<std::string>();
	std::cout << entity_name << std::endl;
	T * entity_pointer = mapping.add(entity_name);
	if(entity_pointer != NULL) {
		iterator->second >> *entity_pointer;
	}
}

#endif
