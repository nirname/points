#ifndef OBJECT_KIND_PARSER_H
#define OBJECT_KIND_PARSER_H 1

void operator >> (const YAML::Node & options, ObjectKind & object_kind) {
	if(options["color"]) {
		object_kind.color = game.colors[options["color"].as<std::string>()];
		if(object_kind.color == NULL) {
			std::cout << OBJECT_IS_NOT_FOUND << " - default is used" << std::endl;
		}
	}
	if(options["shape"]) {
		object_kind.shape = game.shapes[options["shape"].as<std::string>()];
		if(object_kind.shape == NULL) {
			std::cout << OBJECT_IS_NOT_FOUND << " - default is used" << std::endl;
		}
	}
}

#endif
