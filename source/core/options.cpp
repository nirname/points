#include "options.hpp"

namespace options {

	bool proportional = true;
	bool smooth_zooming = true;
	bool multisample = false;

	int window_width = 960;
	int window_height = 540;
	bool full_screen = false;
	bool game_mode = false;

	GRID_TYPE grid_type = SQUARE_GRID;
	void (*default_shape)() = square;
	float padding = 0.0;
	float figure_size = 1.0;
	Color selection_color = Color(BLUE);
	Color clear_color = Color(BLACK);

	bool foreword = true;
	bool afterword = true;
	SCREENSAVER_KIND screensaver_kind = RANDOM_SCREENSAVER;

	int foreword_timeout = 5;
	int menu_timeout = 30;
	int screensaver_timeout = 30;
	int afterword_timeout = 5;

	int min_fps = 20;
	int max_fps = 50;

	//engine::ControlsMapping controls;

	const char * mode_string = "800x600:32";

	void load() {}

}
