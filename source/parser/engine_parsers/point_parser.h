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
