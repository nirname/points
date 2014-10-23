#pragma once

#include "screensaver.hpp"
#include "color.hpp"
#include "grid_type.hpp"

#include "yaml.hpp"

namespace options {

	extern bool proportional;
	extern bool smooth_zooming;
	extern bool multisample;

	extern int window_width;
	extern int window_height;
	extern bool full_screen;
	extern bool game_mode;

	extern GRID_TYPE grid_type;
	extern float padding;
	extern float figure_size;
	extern Color selection_color;
	extern Color clear_color;

	extern bool foreword;
	extern bool afterword;
	extern std::string images_directory;
	extern SCREENSAVER_KIND screensaver_kind;
	extern std::string font_name;

	extern int foreword_timeout;
	extern int menu_timeout;
	extern int screensaver_timeout;
	extern int afterword_timeout;

	extern int min_fps;
	extern int max_fps;

	//engine::ControlsMapping controls;

	extern const char * mode_string;

}

namespace options {

	void load();
	int load_config();
	int save_config();
	void load_options(const YAML::Node & config);

	template<typename OptionType>
	void load_option(OptionType & option, const YAML::Node & config, const char * key);

}
