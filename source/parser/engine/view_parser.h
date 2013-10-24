#ifndef VIEW_PARSER_H
#define VIEW_PARSER_H 1

void operator >> (const YAML::Node & options, View & view) {

	if(options.IsMap()) {

		if(options["field"]) {
			view.field = game.fields[options["field"].as<std::string>()];
		} else {
			throw ATTRIBUTE_IS_MISSED;
		}
		if(view.field == NULL) {
			throw OBJECT_IS_NOT_FOUND;
		}

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

		// TODO use here >> (adds not named color and sets it pointer to view)
		if(options["background_color"]) {
			view.background_color = game.colors[options["background_color"].as<std::string>()];
		}
		if(options["cells_color"]) {
			view.cells_color = game.colors[options["cells_color"].as<std::string>()];
		}
		if(options["grid_color"]) {
			view.grid_color = game.colors[options["grid_color"].as<std::string>()];
		}
		if(options["border_color"]) {
			view.border_color = game.colors[options["border_color"].as<std::string>()];
		}

	} else {
		std::cout << "Options for view should be a mapping" << std::endl;
	}

}

#endif
