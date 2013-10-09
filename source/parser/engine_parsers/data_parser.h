	void operator >> (const YAML::const_iterator & iterator, Data & data) {
		ObjectPointer object = game.objects[iterator->first.as<std::string>()];
		if(object != NULL) {
			Point point;
			iterator->second >> point;
			Data::EFFECT_OF_ADDING effect = data.add(object, point);
			if(effect != Data::ADDED_SUCCESSFULLY) {
				std::cout << "Some problems occured while adding object" << std::endl;
			}
		}
	}
