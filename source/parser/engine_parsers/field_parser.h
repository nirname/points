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
