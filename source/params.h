#pragma once

namespace params
{

	//shape
	//animation
	//format
	extern GRID_TYPE grid_type;
	extern Color color;
	extern SCREENSAVER_KIND screensaver;
	extern bool greeting;
	extern bool goodbuy;
	extern bool full_screen;

	extern int greeting_timeout; // how long greeting is shown
	extern int menu_timeout; // how long we watch the menu till screensaver starts
	extern int screensaver_timeout; // how often we should start it again
	extern int goodbuy_timeout; // how long we watch
	
	extern int window_width;
	extern int window_height;


	SCREENSAVER_KIND screensaver;
	bool greeting;


	int titres_timeout = 5;
	time_t last_menu_activity_time = clock();

	// Screensaver starts after the specified time at seconds
	int menu_timeout = 30;

	int window_width = 0, window_height = 0;
	const char * mode_string;

	bool game_mode = false;
	bool full_screen = false;

	enum WINDOW_SIZE { TINY, SMALL, MIDDLE, LARGE };
	WINDOW_SIZE window_size = SMALL;

	bool save_config() {
		std::cout << "Saving config: " << std::ends;
		std::cout << "No";
		return false;
	}

	void load_parameter(bool & parameter, const YAML::Node & config, const char * key) {
		if(config[key]) {
			const YAML::Node & option = config[key];
			if(option.IsScalar()) {
				std::string value = option.as<std::string>();
				if(value == std::string("on")) {
					parameter = true;
				} else if(value == std::string("off")) {
					parameter = false;
				}
			}
		}
	}
	
	void load_parameter(SCREENSAVER_KIND & parameter, const YAML::Node & config, const char * key) {
		parameter = NO_SCREENSAVER;
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
				std::cout << "Yes" << std::endl;
				return true;
			} else {
				std::cout << "Wrong config format" << std::endl;
			}
		} catch (YAML::ParserException & exception) {
			std::cout << "I can not load config" << std::endl;
		} catch (YAML::BadFile) {
			std::cout << "There is no config" << std::endl;
		}

		return false;
	}

	void load()
	{
	
		std::cout << "\nLoading params\n" << std::endl;
		if(!load_config()) {
			save_config();
		}
		
		switch(window_size)
		{
			case TINY:   window_width = 640,  window_height = 480;  mode_string = "640x480:32";   break;
			case SMALL:  window_width = 800,  window_height = 600;  mode_string = "800x600:32";   break;
			case MIDDLE: window_width = 1024, window_height = 768;  mode_string = "1024x768:32";  break;
			case LARGE:  window_width = 1280, window_height = 1024; mode_string = "1280x1024:32"; break;
			default:     window_width = 1280, window_height = 1024; mode_string = "1280x1024:32"; break;
		}

	}

}
