#ifndef CONTROL_HANDLER_PARSER_H
#define CONTROL_HANDLER_PARSER_H 1

void operator >> (const YAML::Node & options, ControlHandler & handler) {
	if(options.IsMap()) {
		if(options["action"]) {
			//handler.action = MOVE_ACTION;
		} // TODO do action loader
		if(options["option"]) {
			options["option"] >> handler.option;
		}
	}
}

#endif
