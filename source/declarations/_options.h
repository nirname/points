#pragma once

namespace options {

	//extern Shape shape;
	//extern Animation animation;
	//extern SCREEN_FORMAT format;
	//extern graphics::Color color;

	extern GRID_TYPE grid_type;
	extern SCREENSAVER_KIND screensaver_kind;
	extern bool greeting;
	extern bool goodbuy;
	extern bool full_screen;
	extern bool game_mode;

}

namespace options {
	extern time_t last_menu_activity_time;
	extern int menu_timeout;
	extern int titres_timeout;

	extern int greeting_timeout; // how long greeting is shown
	extern int menu_timeout; // how long we watch the menu till screensaver starts
	extern int screensaver_timeout; // how often we should start it again
	extern int goodbuy_timeout; // how long we watch last part
	
	extern int window_width;
	extern int window_height;

	extern int ort;
}

namespace options {

	bool save_config();
	bool load_config();

	template<typename Type> void load_option(Type &, const YAML::Node &, const char * key);
	void load_options(const YAML::Node & config);
	void load();

	void print();

}
