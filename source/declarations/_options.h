#pragma once

extern graphics::Screen screen;
extern engine::Game game;
extern engine::Application application;
extern Interface interface;
extern Screensaver screensaver;

// Public options that are available in 'config.yaml' file
//
namespace params {

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

namespace params {
	extern time_t last_menu_activity_time;
	extern int menu_timeout;
	extern int titres_timeout;
}

// TODO: refactor it
namespace params {

	extern int greeting_timeout; // how long greeting is shown
	extern int menu_timeout; // how long we watch the menu till screensaver starts
	extern int screensaver_timeout; // how often we should start it again
	extern int goodbuy_timeout; // how long we watch last part
	
	extern int window_width;
	extern int window_height;

	extern int ort;
}
