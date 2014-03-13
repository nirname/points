#pragma once

// Params itself
//
namespace params {

	GRID_TYPE grid_type = SQUARE_GRID;
	SCREENSAVER_KIND screensaver = NO_SCREENSAVER;
	bool greeting = true;
	bool full_screen = false;


	int titres_timeout = 5;
	time_t last_menu_activity_time = clock();

	// Screensaver starts after the specified time at seconds
	int menu_timeout = 30;

	int window_width = 0, window_height = 0;
	const char * mode_string;

	bool game_mode = false;

	enum WINDOW_SIZE { TINY, SMALL, MIDDLE, LARGE };
	WINDOW_SIZE window_size = SMALL;

}

// Functions
//
namespace params {

	bool save_config() {
		std::cout << "Saving config: " << std::ends;
		std::cout << "No";
		return false;
	}

	// Loads scalar value
	//
	std::string load_value(const YAML::Node & config, const char * key) {
		if(config[key]) {
			const YAML::Node & option = config[key];
			if(option.IsScalar()) {
				return option.as<std::string>();
			}
		}
		return std::string("");
	}

	// Loads a parameter depending on it's type
	//
	template<typename Type>
	void load_parameter(Type & parameter, const YAML::Node & config, const char * key) {
		std::string value = load_value(config, key);
		value >> parameter;
	}

	bool load_config() {

		std::cout << "Loading config: " << std::ends;
		try {
			YAML::Node config = YAML::LoadFile("config.yaml");
			if(config.IsMap()) {
				load_parameter(full_screen, config, "full_screen");
				load_parameter(screensaver, config, "screensaver");
				load_parameter(greeting, config, "screensaver");

				//load_parameter(config, "grid_type");
				std::cout << "Yes\n" << std::endl;
				return true;
			} else {
				std::cout << "Wrong config format" << std::endl;
			}
		} catch (YAML::ParserException & exception) {
			std::cout << "I can not load config" << std::endl;
		} catch (YAML::BadFile) {
			std::cout << "There is no config" << std::endl;
		}
		std::cout << std::endl;
		return false;
	}

	void load() {

		std::cout << "\nLoading params\n" << std::endl;
		if(!load_config()) {
			save_config();
		}

		switch(window_size) {
			case TINY:   window_width = 640,  window_height = 480;  mode_string = "640x480:32";   break;
			case SMALL:  window_width = 800,  window_height = 600;  mode_string = "800x600:32";   break;
			case MIDDLE: window_width = 1024, window_height = 768;  mode_string = "1024x768:32";  break;
			case LARGE:  window_width = 1280, window_height = 1024; mode_string = "1280x1024:32"; break;
			default:     window_width = 1280, window_height = 1024; mode_string = "1280x1024:32"; break;
		}

	}
	
	void print() {

		std::cout << "screensaver: " << screensaver << std::endl;
		std::cout << "full_screen: " << full_screen << std::endl;
		//std::cout << "color: " << color << std::endl;
		std::cout << "greeting: " << greeting << std::endl;
		
	}

}
