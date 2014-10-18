#include "application.hpp"

#include <cstdlib>
#include "controls.hpp"
#include "options.hpp"
#include "variables.hpp"
#include "opengl.hpp"

#include <iostream>

Application::Application() {
	mode = LOADING_MODE;
}

void Application::set(APPLICATION_MODE _mode) {
	APPLICATION_MODE previous_mode = mode;
	mode = LOADING_MODE;
	switch(_mode) {
		case LOADING_MODE: {
			break;
		}
		case FOREWORD_MODE: {
			if(foreword.load()) {
				screen.set(foreword.input.TellWidth(), foreword.input.TellHeight());
			}
			//glutTimerFunc(options::foreword_timeout * 1000, menu_autoload, 0);
			break;
		}
		case MENU_MODE: {
			interface.reset_last_activity_time();
			if(game.loaded) {
				game.pause();
			}
			break;
		}
		case SCREENSAVER_MODE: {
			if(options::screensaver_kind != NO_SCREENSAVER) {
				screen.set(screensaver.width, screensaver.height);
			} else {
				_mode = previous_mode;
			}
			break;
		}
		case COUNTDOWN_MODE: {
			break;
		}
		case GAMEPLAY_MODE: {
			if(game.loaded) {
				screen.set(game.screen_size.width, game.screen_size.height);
				if(game.paused) {
					game.resume();
				}
			} else {
				_mode = previous_mode;
			}
			break;
		}
		case INFORMATION_MODE: {
			//if(!game.paused) {
			//	game.pause();
			//}
			break;
		}
		case AFTERWORD_MODE: {
			//glutTimerFunc(options::afterword_timeout * 1000, auto_exit, 0);
			break;
		}
	}
	mode = _mode;
}

void Application::start() {
	if(options::foreword) {
		set(FOREWORD_MODE);
	} else {
		set(MENU_MODE);
	}
}

void Application::quit() {
	if(options::afterword) {
		set(AFTERWORD_MODE);
	} else {
		glutLeaveMainLoop();
	}
}

void Application::handle(unsigned char key, int special_key) {

	if(key == CTRL_Q_KEY) {
		std::cout << "Ctrl+Q" << std::endl;
		std::cout << "GOODBYE" << std::endl;
		glutLeaveMainLoop();
	}

	std::cout << "key: " << (unsigned int)key << ", special key: " << special_key << std::endl;

	switch(mode) {
		case LOADING_MODE: {
			/*TODO: show a joke or something else */ break;
		}
		case FOREWORD_MODE: {
			if(key != 0) {
				foreword.skip();
				set(MENU_MODE);
			}
			break;
		}
		case MENU_MODE: {
			interface.handle(key, special_key);
			break;
		}
		case SCREENSAVER_MODE: {
			screensaver.skip();
			set(MENU_MODE);
			break;
		}
		case COUNTDOWN_MODE: {
			break;
		}
		case GAMEPLAY_MODE: {
			if(key == ESCAPE_KEY) {
				set(MENU_MODE);
			} else {
				game.handle(key, special_key);
			}
			break;
		}
		case INFORMATION_MODE: {
			// resume && continue game
			break;
		}
		case AFTERWORD_MODE: {
			if(key != 0) {
				//afterword.skip(); // && exit;
				std::cout << "GOODBYE" << std::endl;
				glutLeaveMainLoop();
			}
			break;
		}
	}

}
