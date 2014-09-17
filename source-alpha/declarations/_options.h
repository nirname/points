#pragma once

namespace options {

	extern float padding;
	extern float figure_size;

	extern bool proportional;
	extern bool smooth_zooming;
	extern bool multisample;

	extern GRID_TYPE grid_type;
	
	extern SCREENSAVER_KIND screensaver_kind;
	
	extern bool foreword;
	extern bool afterword;
	extern bool full_screen;
	extern bool game_mode;

	extern int window_width;
	extern int window_height;

	// Duration for each stage
	extern int foreword_timeout;
	extern int menu_timeout;
	extern int screensaver_timeout;
	extern int afterword_timeout;

	//extern SCREEN_FORMAT format;
	//extern Shape shape;
	//extern Animation animation;
	extern graphics::Color selection_color;
	extern graphics::Color clear_color;

}

namespace options {

	extern time_t last_menu_activity_time;
	extern const char * mode_string;

}

namespace options {

	bool save_config();
	bool load_config();

	template<typename Type> void load_option(Type &, const YAML::Node &, const char * key);
	void load_options(const YAML::Node & config);
	void load();

	void print();

}
