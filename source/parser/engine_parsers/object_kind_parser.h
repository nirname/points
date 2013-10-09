	void operator >> (const YAML::Node & options, ObjectKind & object_kind) {
		if(options["color"]) {
			object_kind.color = game.colors[options["color"].as<std::string>()];
		}
		if(options["shape"]) {
			object_kind.shape = game.shapes[options["shape"].as<std::string>()];
		}
	}
