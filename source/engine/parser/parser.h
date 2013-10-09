	void operator >> (const YAML::Node & options, Size & size) {
		try {
			if(options.IsMap()) {
				if(options["width"] != NULL && options["height"] != NULL) {
					size.width = options["width"].as<int>();
					size.height = options["height"].as<int>();
				}
			} else if (options.IsSequence()) {
				if(options.size() == 1) {
					size.height = size.width = options[0].as<int>();
				} else if(options.size() == 2) {
					size.width = options[0].as<int>();
					size.height = options[1].as<int>();
				} else {
					std::cout << "Wrong number of arguments for size" << std::endl;
				}
			} else if (options.IsScalar()) {
				size.height = size.width = options.as<int>();
			} else {
				std::cout << "Size options should be scalar or map" << std::endl;
			}
		} catch(YAML::TypedBadConversion<int> & exception) {
			std::cout << "Size should be an integer " << std::endl;
			size.width = 1;
			size.height = 1;
		}
		if(size.width <= 0) {
			size.width = 1;
			std::cout << "Any size dimension should be greater than 0" << std::endl;
		}
		if(size.height <= 0) {
			size.height = 1;
			std::cout << "Any size dimension should be greater than 0" << std::endl;
		}
	}

	void operator >> (const YAML::Node & options, Point & point) {
		try {
			if(options.IsMap()) {
				if(options["row"] != NULL && options["column"] != NULL) {
					point.row = options["row"].as<int>();
					point.column = options["column"].as<int>();
				}
			} else if (options.IsSequence()) {
				if(options.size() == 1) {
					point.column = point.row = options[0].as<int>();
				} else if(options.size() == 2) {
					point.column = options[0].as<int>();
					point.row = options[1].as<int>();
				} else {
					std::cout << "Wrong number of arguments for point" << std::endl;
				}
			} else if (options.IsScalar()) {
				point.column = point.row = options.as<int>();
			} else {
				std::cout << "Point options should be scalar or map" << std::endl;
			}
		} catch(YAML::TypedBadConversion<int> & exception) {
			std::cout << "Point dimension should be an integer " << std::endl;
		}
	}

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

	void operator >> (const YAML::Node & options, Field & field) {
		if(options.IsMap()) {
			if(options["size"]) {
				options["size"] >> field.size;
			}
			if(options["closure"]) {
			}
			if(options["data"]) {
				const YAML::Node & data_node = options["data"];
				if(data_node.IsMap()) {
					for(YAML::const_iterator iterator = data_node.begin(); iterator != data_node.end(); ++iterator) {
						iterator >> field.data;
					}
				} else if (data_node.IsSequence()) {
					std::cout << "<<<<<<<<<<SEQUENCE" << std::endl;
				}

			}
		} else {
			std::cout << "Options for field should be a mapping" << std::endl;
		}
	}

	void operator >> (const YAML::Node & options, ObjectKind & object_kind) {
		if(options["color"]) {
			object_kind.color = game.colors[options["color"].as<std::string>()];
		}
		if(options["shape"]) {
			object_kind.shape = game.shapes[options["shape"].as<std::string>()];
		}
	}

	void operator >> (const YAML::Node & options, View & view) {
		if(options.IsMap()) {
			view.field = game.fields[options["field"].as<std::string>()];
			if(options["size"]) {
				options["size"] >> view.size;
			} else {
				view.adjust_size();
			}
			if(options["offset"]) {
				options["offset"] >> view.offset;
			}
			if(options["position"]) {
				options["position"] >> view.position;
			}
		} else {
			std::cout << "Options for view should be a mapping" << std::endl;
		}
	}

	void operator >> (const YAML::Node & options, ControlHandler & handler) {
		if(options.IsMap()) {
			if(options["object"]) handler.object = game.objects[options["object"].as<std::string>()];
			if(options["action"]) handler.action = MOVE;
			if(options["option"]) options["option"] >> handler.option;
		}
		//ObjectPointer object = game.objects[->first.as<std::string>()];
		//if(object != NULL) {
			//YAML::NodeType::value node_type = iterator->second.Type();
		//}
	}
