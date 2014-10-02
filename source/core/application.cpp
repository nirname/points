#include "application.hpp"

#include <cstdlib>
#include "controls.hpp"
#include "options.hpp"
#include "variables.hpp"
#include "opengl.hpp"

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
			//interface.reset_last_activity_time();
			//reset_last_activity_time();
			//if(game.loaded) {
			//	game.pause();
			//}
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
			//if(game.loaded) {
			//	if(game.paused) {
			//		game.resume();
			//	}
			//	screen.set(game.screen_size.width, game.screen_size.height);
			//} else {
				_mode = previous_mode;
			//}
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
		std::cout << " -> quit" << std::endl;
		glutLeaveMainLoop();
		//exit(EXIT_SUCCESS);
	}
}

void Application::handle(unsigned char key, int special_key) {

	if(key == CTRL_Q_KEY) {
		exit(EXIT_SUCCESS);
	}

	switch(mode) {
		case LOADING_MODE: {
			/*TODO: show a joke or something else */ break;
		}
		case FOREWORD_MODE: {
			foreword.skip(); // skip
			set(MENU_MODE);
			break;
		}
		case MENU_MODE: {
			interface.handle(key, special_key);
			break;
		}
		case SCREENSAVER_MODE: {
			screensaver.skip();
			set(MENU_MODE); // skip
			break;
		}
		case COUNTDOWN_MODE: {
			break;
		}
		case GAMEPLAY_MODE: {
			if(key == ESCAPE_KEY) {
				set(MENU_MODE);
			} else {
				//game.handle(key, special_key);
			}
			break;
		}
		case INFORMATION_MODE: {
			// resume && continue game
			break;
		}
		case AFTERWORD_MODE: {
			/*if(key != 0) {
				std::cout << " -> quit" << std::endl;
				exit(EXIT_SUCCESS);
			}*/
			break;
		}
	}

}

/*	void Application::foreword_process(unsigned char key, int special_key) {
		if(key != 0) {
			std::cout << " -> skip";
			set(MENU_MODE);
		}
	}

	void Application::menu_process(unsigned char key, int special_key) {
		reset_last_activity_time();
		interface.handle(key, special_key);
	}

	void Application::gameplay_process(unsigned char key, int special_key) {
		if(key == ESCAPE_KEY) {
			set(MENU_MODE);
		} else {
			game.process(key, special_key);
		}
	}

	void Application::screensaver_process(unsigned char key, int special_key) {
		std::cout << " -> skip ";
		set(MENU_MODE);
	}

	void Application::afterword_process(unsigned char key, int special_key) {
		if(key != 0) {
			std::cout << " -> quit" << std::endl;
			exit(EXIT_SUCCESS);
		}
	}
*/
