#pragma once

namespace options {

	float padding = 0.0;
	float figure_size = 1.0;

	bool proportional = true;
	bool smooth_zooming = true;
	bool multisample = false;

	GRID_TYPE grid_type = SQUARE_GRID;

	SCREENSAVER_KIND screensaver_kind = RANDOM_SCREENSAVER;

	bool foreword = true;
	bool afterword = true;
	bool full_screen = false;
	bool game_mode = false;

	int window_width = 960;
	int window_height = 540;

	int foreword_timeout = 5;
	int menu_timeout = 30;
	int screensaver_timeout = 30;
	int afterword_timeout = 5;

	graphics::Color selection_color = Color(BLUE);
	//graphics::Color clear_color = Color(BLACK);

	//engine::ControlsMapping controls;

}

namespace options {

	time_t last_menu_activity_time = clock();
	const char * mode_string = "800x600:32";

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

		load_option(padding, config, "padding");
		padding = std::min( std::max(padding, 0.0f), 0.25f );
		figure_size = 1.0f - padding * 2;

		load_option(proportional, config, "proportional");
		load_option(smooth_zooming, config, "smooth_zooming");
		load_option(multisample, config, "multisample");

		load_option(graphics::default_shape, config, "shape");

		load_option(grid_type, config, "grid_type");

		load_option(screensaver_kind, config, "screensaver");

		load_option(foreword, config, "foreword");
		load_option(afterword, config, "afterword");
		load_option(full_screen, config, "full_screen");
		load_option(game_mode, config, "game_mode");

		load_option(window_width, config, "window_width");
		load_option(window_height, config, "window_height");

		load_option(foreword_timeout, config, "foreword_timeout");
		load_option(menu_timeout, config, "menu_timeout");
		load_option(screensaver_timeout, config, "screensaver_timeout");
		load_option(afterword_timeout, config, "afterword_timeout");

		load_option(selection_color, config, "selection_color");
		//load_option(clear_color, config, "clear_color");

	}

	// Parses config file
	//
	bool load_config() {
		std::cout << "Loading config: " << std::ends;
		try {
			YAML::Node config = YAML::LoadFile("config.yaml");
			if(config.IsMap()) {
				load_options(config); // Loading itself
				std::cout << "Yes" << std::endl;
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
		if(!load_config()) {
			save_config();
		}
		print();
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
