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
