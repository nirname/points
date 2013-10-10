#ifndef CONTROL_HANDLER_PARSER_H
#define CONTROL_HANDLER_PARSER_H 1

void operator >> (const YAML::Node & options, ControlHandler & handler) {
	if(options.IsMap()) {
		if(options["object"]) {
			handler.object = game.objects[options["object"].as<std::string>()];
			if(handler.object == NULL) {
				throw OBJECT_IS_NOT_FOUND;
			}
		} else {
			throw ATTRIBUTE_IS_MISSED;
		}
		if(options["action"]) handler.action = MOVE; // !!! do action loader
		if(options["option"]) options["option"] >> handler.option;
	}
}

#endif
