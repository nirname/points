#ifndef PARAMS_H
#define PARAMS_H 1

namespace params
{

	int time_to_menu_autoload = 5000;

	int window_width = 0, window_height = 0;
	const char * mode_string;

	bool game_mode = false;
	bool full_screen = false;
	unsigned int display_mode = 0;

	enum WINDOW_SIZE { TINY, SMALL, MIDDLE, LARGE };
	WINDOW_SIZE window_size = SMALL;

	void load()
	{

		display_mode = GLUT_RGB | GLUT_DOUBLE;
		switch(window_size)
		{
			case TINY:   window_width = 640,  window_height = 480;  mode_string = "640x480:32";   break;
			case SMALL:  window_width = 800,  window_height = 600;  mode_string = "800x600:32";   break;
			case MIDDLE: window_width = 1024, window_height = 768;  mode_string = "1024x768:32";  break;
			case LARGE:  window_width = 1280, window_height = 1024; mode_string = "1280x1024:32"; break;
			default:     window_width = 1280, window_height = 1024; mode_string = "1280x1024:32"; break;
		}

		// TODO load config.yaml here

	}

}

#endif
