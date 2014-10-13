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

	void load() {
		if(load_config() == 1) {
			save_config();
		}
	}

	/// Load config file
	//
	/// 0 - everything is ok
	/// 1 - file not found
	/// 2 - syntax errors inside
	/// 3 - wrong format / is not a map
	///
	int load_config() {
		try {
			YAML::Node config = YAML::LoadFile("config.yaml");
			if(config.IsMap()) {
				load_options(config);
			} else {
				return 3;
			}
		} catch (YAML::ParserException & exception) {
			return 2;
		} catch (YAML::BadFile) {
			return 1;
		}
		std::cout << std::endl;
		return 0;
	}

	int save_config() {
		return 0;
	}

	void load_options(const YAML::Node & config) {
	}

}
