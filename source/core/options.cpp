#include "options.hpp"

#include <iostream>
#include "emitter.hpp"
#include "shape.hpp"
#include "convert.hpp"

namespace options {

	bool proportional = true;
	bool smooth_zooming = true;
	bool multisample = false;

	int window_width = 960;
	int window_height = 540;
	bool full_screen = false;
	bool game_mode = false;

	GRID_TYPE grid_type = SQUARE_GRID;
	float padding = 0.0;
	float figure_size = 1.0;
	Color selection_color = Color(BLUE);
	Color clear_color = Color(BLACK);

	bool foreword = true;
	bool afterword = true;
	std::string images_directory = "images/";
	std::string font_name = "mono-55";
	std::string fonts_directory = "fonts/";
	SCREENSAVER_KIND screensaver_kind = RANDOM_SCREENSAVER;

	int foreword_timeout = 5;
	int menu_timeout = 30;
	int screensaver_timeout = 30;
	int afterword_timeout = 5;

	int min_fps = 20;
	int max_fps = 50;

	//engine::ControlsMapping controls;

	const char * mode_string = "800x600:32";

	void load() {
		if(load_config() == 1) {
			save_config();
		}
	}

	/// Load config file
	//
	/// 0 - everything is ok
	/// 1 - file not found
	/// 2 - syntax errors inside
	/// 3 - wrong format / is not a map
	///
	int load_config() {
		std::cout << "Loading config: " << std::ends;
		try {
			YAML::Node config = YAML::LoadFile("config/settings.yaml");
			if(config.IsMap()) {
				std::cout << "ok" << std::endl;
				load_options(config);
			} else {
				std::cout << "config is not a map" << std::endl;
				return 3;
			}
		} catch (YAML::ParserException & exception) {
			std::cout << "syntax errors" << std::endl;
			return 2;
		} catch (YAML::BadFile) {
			std::cout << "no config or file is corrupted" << std::endl;
			return 1;
		}
		return 0;
	}

	int save_config() {
		std::cout << "Saving config: " << std::ends;
		std::cout << "no" << std::endl;
		return 0;
	}

	/// Load an option depending on it's type
	//
	/// 0 - option is loaded
	/// 1 - option is wrong, default value is used
	/// 2 - option is omitted, default value is used
	template<typename OptionType>
	void load_option(OptionType & option, const YAML::Node & config, const char * key) {
		std::cout << "  " << key << ": " << std::ends;
		if(config[key]) {
			try {
				option = config[key].as<OptionType>();
				std::cout << "ok" << std::ends;
			} catch(YAML::TypedBadConversion<OptionType> & exception) {
				std::cout << "wrong value" << std::ends;
			}
		} else {
			std::cout << "default" << std::ends;
		}
		//std::cout << std::endl;
		std::cout << " - " << option << std::endl;
	}

	void load_options(const YAML::Node & config) {

		std::cout << "Loading options:" << std::endl;

		load_option(proportional, config, "proportional");
		load_option(smooth_zooming, config, "smooth_zooming");
		load_option(multisample, config, "multisample");

		load_option(window_width, config, "window_width");
		load_option(window_height, config, "window_height");
		load_option(full_screen, config, "full_screen");
		load_option(game_mode, config, "game_mode");

		//load_option(grid_type, config, "grid_type");
		load_option(padding, config, "padding");
		padding = std::min( std::max(padding, 0.0f), 0.25f );
		figure_size = 1.0f - padding * 2;
		load_option(selection_color, config, "selection_color");
		load_option(default_shape, config, "shape");
		load_option(clear_color, config, "clear_color");

		load_option(foreword, config, "foreword");
		load_option(afterword, config, "afterword");
		load_option(images_directory, config, "images_directory");
		load_option(font_name, config, "font_name");
		load_option(fonts_directory, config, "fonts_directory");
		//load_option(screensaver_kind, config, "screensaver_kind");

		load_option(foreword_timeout, config, "foreword_timeout");
		load_option(menu_timeout, config, "menu_timeout");
		load_option(screensaver_timeout, config, "screensaver_timeout");
		load_option(afterword_timeout, config, "afterword_timeout");

		std::cout << "ok" << std::endl;
	}

}
