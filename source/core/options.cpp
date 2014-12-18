#include "options.hpp"

#include <iostream>
#include "emitter.hpp"
#include "convert.hpp"

#include <fstream>

namespace options {

	bool proportional = true;
	bool smooth_zooming = true;
	bool multisample = true;

	AspectRatio aspect_ratio(16, 9);
	bool full_screen = true;
	bool game_mode = false;
	int window_width = 960;
	int window_height = 540;

	GRID_TYPE grid_type = SQUARE_GRID;
	int padding = 1;
	Color clear_color = Color(WHITE);
	Color base_color = Color(BLACK);
	Color selection_color = Color(BLACK);

	bool foreword = true;
	bool afterword = true;

	YAML::Node shape_options = YAML::Node("block");
	std::string images_directory = "images/";
	std::string font_name = "mono-55";
	std::string fonts_directory = "fonts/";
	SCREENSAVER_KIND screensaver_kind = RANDOM_SCREENSAVER;
	std::string levels_directory = "levels/";

	int foreword_timeout = 5;
	int menu_timeout = 30;
	int screensaver_timeout = 30;
	int afterword_timeout = 5;

	int min_fps = 20;
	int max_fps = 50;

	//engine::ControlsMapping controls;

	const char * mode_string = "800x600:32";

	float figure_size() {
		return 1.0 - 0.05 * padding * 2;
	}

}


namespace options {

	void load() {
		if(load_config() > 0) {
			save_config();
		}
	}

	/// Load config file
	//
	/// 0 - everything is ok
	/// 1 - with omitted values
	/// 2 - with wrong values
	/// 3 - wrong format / is not a map
	/// 4 - syntax errors inside
	/// 5 - file not found
	///
	int load_config() {
		std::cout << "Config: " << std::ends;
		try {
			YAML::Node config = YAML::LoadFile("config/settings.yaml");
			if(config.IsMap()) {
				std::cout << "ok" << std::endl;
				return load_options(config);
			} else {
				std::cout << "config is not a map" << std::endl;
				return 3;
			}
		} catch (YAML::ParserException & exception) {
			std::cout << "syntax errors" << std::endl;
			return 4;
		} catch (YAML::BadFile) {
			std::cout << "config file does not exist or corrupted" << std::endl;
			return 5;
		}
	}

	/// Load an option depending on it's type
	//
	/// 0 - option is loaded
	/// 1 - option is omitted, default value is used
	/// 2 - option is wrong, default value is used
	///
	template<typename OptionType>
	int load_option(OptionType & option, const YAML::Node & config, const char * key) {
		std::cout << "  " << key << ": " << std::ends;
		if(config[key]) {
			try {
				option = config[key].as<OptionType>();
				std::cout << "ok" << std::ends;
			} catch(YAML::TypedBadConversion<OptionType> & exception) {
				std::cout << "wrong value" << std::endl;
				return 2;
			}
		} else {
			std::cout << "default" << std::endl;
			return 1;
		}
		std::cout << " - " << option << std::endl;
		return 0;
	}

	int load_options(const YAML::Node & config) {

		int result = 0;

		std::cout << "Options: " << std::endl;

		result |= load_option(proportional, config, "proportional");
		result |= load_option(smooth_zooming, config, "smooth_zooming");
		result |= load_option(multisample, config, "multisample");

		result |= load_option(aspect_ratio, config, "aspect_ratio");
		result |= load_option(full_screen, config, "full_screen");
		result |= load_option(game_mode, config, "game_mode");
		result |= load_option(window_width, config, "window_width");
		result |= load_option(window_height, config, "window_height");

		//load_option(grid_type, config, "grid_type");
		result |= load_option(padding, config, "padding");
		if(padding < -5 || 5 < padding) padding = 1;
		result |= load_option(base_color, config, "base_color");
		result |= load_option(selection_color, config, "selection_color");

		//load_option(shape_options, config, "shape");
		result |= load_option(clear_color, config, "clear_color");

		result |= load_option(foreword, config, "foreword");
		result |= load_option(images_directory, config, "images_directory");
		result |= load_option(afterword, config, "afterword");
		result |= load_option(font_name, config, "font_name");
		result |= load_option(fonts_directory, config, "fonts_directory");
		result |= load_option(screensaver_kind, config, "screensaver_kind");
		result |= load_option(levels_directory, config, "levels_directory");

		result |= load_option(foreword_timeout, config, "foreword_timeout");
		result |= load_option(menu_timeout, config, "menu_timeout");
		result |= load_option(screensaver_timeout, config, "screensaver_timeout");
		result |= load_option(afterword_timeout, config, "afterword_timeout");

		std::cout << "ok" << std::endl;

		return result;
	}

	void build_config(YAML::Node & config) {
		config["proportional"] = proportional;
		config["smooth_zooming"] = smooth_zooming;
		config["multisample"] = multisample;

		config["window_width"] = window_width;
		config["window_height"] = window_height;
		config["aspect_ratio"] = aspect_ratio;
		config["full_screen"] = full_screen;
		config["game_mode"] = game_mode;

		//load_option(grid_type, config, "grid_type");
		config["padding"] = padding;
		config["base_color"] = base_color;
		config["selection_color"] = selection_color;

		//config["shape"] = shape_options;
		//load_option(shape_options, config, "shape");
		config["clear_color"] = clear_color;

		config["foreword"] = foreword;
		config["afterword"] = afterword;
		config["images_directory"] = images_directory;
		config["font_name"] = font_name;
		config["fonts_directory"] = fonts_directory;
		config["screensaver_kind"] = screensaver_kind;
		config["levels_directory"] = levels_directory;

		config["foreword_timeout"] = foreword_timeout;
		config["menu_timeout"] = menu_timeout;
		config["screensaver_timeout"] = screensaver_timeout;
		config["afterword_timeout"] = afterword_timeout;
	}

	int save_config() {
		std::cout << "Saving config: " << std::ends;

		YAML::Node config;
		build_config(config);

		YAML::Emitter yaml;
		yaml << config;

		std::ofstream file("config/settings.yaml");
		if(file.good() && file.is_open()) {
			file << yaml.c_str();
			std::cout << "yes" << std::endl;
		} else {
			std::cout << "no" << std::endl;
		}
		file.close();

		return 0;
	}

}
