#include "options.hpp"

#include <iostream>
#include "emitter.hpp"
#include "convert.hpp"
#include "yaml_adapter.hpp"

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

	int load_config() {
		return load_yaml_file(config_file_path, load_options);
	}

	int save_config() {
		return save_yaml_file(config_file_path, save_options);
	}

	int load_options(const YAML::Node & config) {
		int result = 0;

		std::cout << "Options: " << std::endl;

		result |= load_yaml_option(proportional, config, "proportional");
		result |= load_yaml_option(smooth_zooming, config, "smooth_zooming");
		result |= load_yaml_option(multisample, config, "multisample");

		result |= load_yaml_option(aspect_ratio, config, "aspect_ratio");
		result |= load_yaml_option(full_screen, config, "full_screen");
		result |= load_yaml_option(game_mode, config, "game_mode");
		result |= load_yaml_option(window_width, config, "window_width");
		result |= load_yaml_option(window_height, config, "window_height");

		//load_yaml_option(grid_type, config, "grid_type");
		result |= load_yaml_option(padding, config, "padding");
		if(padding < -5 || 5 < padding) { padding = 1; }
		result |= load_yaml_option(base_color, config, "base_color");
		result |= load_yaml_option(selection_color, config, "selection_color");

		result |= load_yaml_option(shape_options, config, "shape_options");
		result |= load_yaml_option(clear_color, config, "clear_color");

		result |= load_yaml_option(foreword, config, "foreword");
		result |= load_yaml_option(images_directory, config, "images_directory");
		result |= load_yaml_option(afterword, config, "afterword");
		result |= load_yaml_option(font_name, config, "font_name");
		result |= load_yaml_option(fonts_directory, config, "fonts_directory");
		result |= load_yaml_option(screensaver_kind, config, "screensaver_kind");
		result |= load_yaml_option(levels_directory, config, "levels_directory");

		result |= load_yaml_option(foreword_timeout, config, "foreword_timeout");
		result |= load_yaml_option(menu_timeout, config, "menu_timeout");
		result |= load_yaml_option(screensaver_timeout, config, "screensaver_timeout");
		result |= load_yaml_option(afterword_timeout, config, "afterword_timeout");

		std::cout << "ok" << std::endl;

		return result;
	}

	int save_options(YAML::Node & config) {
		config["proportional"] = proportional;
		config["smooth_zooming"] = smooth_zooming;
		config["multisample"] = multisample;

		config["window_width"] = window_width;
		config["window_height"] = window_height;
		config["aspect_ratio"] = aspect_ratio;
		config["full_screen"] = full_screen;
		config["game_mode"] = game_mode;

		//config["grid_type"] = grid_type;
		config["padding"] = padding;
		config["base_color"] = base_color;
		config["selection_color"] = selection_color;

		config["shape_options"] = shape_options;
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

		return 0;
	}

}
