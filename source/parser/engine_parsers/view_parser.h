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

		// !!! use here >> (adds not named color and sets it pointer to view)
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
