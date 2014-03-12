#pragma once

namespace params
{

	extern int titres_timeout;
	extern int menu_timeout; // screensaver_timeout
	extern int window_width;
	extern int window_height;
	extern bool full_screen;

	// TODO: convert titres timeout to seconds or menu timeout to msec
	int titres_timeout = 5;
	time_t last_menu_activity_time = clock();

	// Screensaver starts after the specified time at seconds
	int menu_timeout = 30; // TODO: convert this one to msec

	int window_width = 0, window_height = 0;
	const char * mode_string;

	bool game_mode = false;
	bool full_screen = false;

	enum WINDOW_SIZE { TINY, SMALL, MIDDLE, LARGE };
	WINDOW_SIZE window_size = SMALL;

	void load()
	{

		// TODO load config.yaml here

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
