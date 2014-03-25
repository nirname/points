#pragma once

namespace options {

	GRID_TYPE grid_type = SQUARE_GRID;

	SCREENSAVER_KIND screensaver_kind;

	bool foreword = true;
	bool afterword = true;
	bool full_screen = false;
	bool game_mode = false;

}

namespace options {

	int ort;
	int titres_timeout = 5;
	time_t last_menu_activity_time = clock();

	// Screensaver starts after the specified time at seconds
	int menu_timeout = 30;

	int window_width = 0;
	int window_height = 0;
	const char * mode_string;

	//enum WINDOW_SIZE { TINY, SMALL, MIDDLE, LARGE };
	//WINDOW_SIZE window_size = SMALL;

}

namespace options {

	// Saves config with current values
	//
	bool save_config() {
		std::cout << "Saving config: " << std::ends;
		std::cout << "No";
		return false;
	}

	// Loads an option depending on it's type
	//
	template<typename Type>
	void load_option(Type & parameter, const YAML::Node & config, const char * key) {
		if(config[key]) {
			const YAML::Node & option = config[key];
			option >> parameter;
		}
	}

	// Loads all options
	//
	void load_options(const YAML::Node & config) {
		//load_option(grid_type, config, "grid_type");
		load_option(screensaver_kind, config, "screensaver");
		load_option(full_screen, config, "full_screen");
		load_option(foreword, config, "greeting");
		load_option(afterword, config, "afterword");
		load_option(window_width, config, "window_width");
		load_option(window_height, config, "window_height");
	}

	// Parses config file
	//
	bool load_config() {
		std::cout << "Loading config: " << std::ends;
		try {
			YAML::Node config = YAML::LoadFile("config.yaml");
			if(config.IsMap()) {
				load_options(config); // Loading itself
				std::cout << "Yes\n" << std::endl;
				return true;
			} else {
				std::cout << "Config should contain 'key: value' pairs" << std::endl;
			}
		} catch (YAML::ParserException & exception) {
			std::cout << "Wrong syntax" << std::endl;
		} catch (YAML::BadFile) {
			std::cout << "No config file" << std::endl;
		}
		std::cout << std::endl;
		return false;
	}

	void load() {

		window_width = 960;
		window_height = 540;
		mode_string = "800x600:32";
		std::cout << "\nLoading params\n" << std::endl;
		if(!load_config()) {
			save_config();
		}

		print();
		/*switch(window_size) {
			case TINY:   window_width = 640,  window_height = 480;  mode_string = "640x480:32";   break;
			case SMALL:  window_width = 800,  window_height = 600;  mode_string = "800x600:32";   break;
			case MIDDLE: window_width = 1024, window_height = 768;  mode_string = "1024x768:32";  break;
			case LARGE:  window_width = 1280, window_height = 1024; mode_string = "1280x1024:32"; break;
			default:     window_width = 1280, window_height = 1024; mode_string = "1280x1024:32"; break;
		}*/

	}
	
	void print() {

		std::cout << "grid_type: "   << grid_type        << std::endl;
		std::cout << "screensaver: " << screensaver_kind << std::endl;
		std::cout << "foreword: "    << foreword         << std::endl;
		std::cout << "afterword: "   << afterword        << std::endl;
		std::cout << "full_screen: " << full_screen      << std::endl;
		std::cout << "game_mode: "   << game_mode        << std::endl;

	}

}
