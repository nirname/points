#pragma once

// Public options that are available in 'config.yaml' file
//
namespace params {

	//extern Shape shape;
	//extern Animation animation;
	//extern SCREEN_FORMAT format;
	extern GRID_TYPE grid_type;
	//extern graphics::Color color;
	extern Screensaver screensaver;
	extern bool greeting;
	extern bool goodbuy;
	extern bool full_screen;

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
