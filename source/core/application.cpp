#include "application.hpp"

#include <cstdlib>
#include "keys.hpp"
#include "options.hpp"
#include "variables.hpp"
#include "opengl.hpp"

#include <iostream>
#include "emitters.hpp"

Application::Application() {
	mode = LOADING_MODE;
}

bool Application::set(APPLICATION_MODE next_mode) {
	APPLICATION_MODE previous_mode = mode;
	mode = LOADING_MODE;
	switch(next_mode) {
		case LOADING_MODE: {
			break;
		}
		case FOREWORD_MODE: {
			if(foreword.loaded || foreword.load()) {
				screen.set(foreword.input.TellWidth(), foreword.input.TellHeight());
			} else {
				next_mode = previous_mode;
			}
			break;
		}
		case MENU_MODE: {
			screen.set(21 * font.height, options::aspect_ratio);
			reset_last_menu_activity_time();
			if(game.loaded) {
				game.pause();
			}
			if(screensaver.is_loaded()) {
				screensaver.skip();
			}
			break;
		}
		case SCREENSAVER_MODE: {
			if(screensaver.is_loaded()) {
				screen.set(screensaver.width(), screensaver.height());
			} else {
				next_mode = previous_mode;
			}
			break;
		}
		case COUNTDOWN_MODE: {
			break;
		}
		case GAMEPLAY_MODE: {
			if(game.loaded) {
				screen.set(game.width(), game.height());
				if(game.paused) {
					game.resume();
				}
			} else {
				next_mode = previous_mode;
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
			glutTimerFunc(options::afterword_timeout * 1000, auto_exit, 0);
			break;
		}
	}
	if(mode == next_mode) {
		return false;
	} else {
		mode = next_mode;
		std::cout << mode << std::endl;
	}
	return true;
}

void Application::start() {
	if(options::foreword && set(FOREWORD_MODE)) {
		glutTimerFunc(options::foreword_timeout * 1000, menu_autoload, 1);
	} else {
		set(MENU_MODE);
	}
	glutTimerFunc(10 * 1000, screensaver_autoload, 0);
}

void Application::quit(bool quit_immidiately) {
	if(!quit_immidiately && options::afterword) {
		set(AFTERWORD_MODE);
	} else {
		std::cout << "\nGOODBYE\n" << std::endl;
		glutLeaveMainLoop();
	}
}

void Application::handle(unsigned char key, int special_key) {

	std::cout << "key: " << (unsigned int)key << ", special key: " << special_key << std::endl;

	if(key == CTRL_Q_KEY) {
		std::cout << "Ctrl+Q" << std::endl;
		quit(true);
	}

	switch(mode) {
		case LOADING_MODE: {
			/*TODO: show a jgoke or something else */ break;
		}
		case FOREWORD_MODE: {
			if(key != 0) {
				//foreword.skip();
				set(MENU_MODE);
			}
			break;
		}
		case MENU_MODE: {
			reset_last_menu_activity_time();
			interface.handle(key, special_key);
			break;
		}
		case SCREENSAVER_MODE: {
			if(key != 0) {
				screensaver.skip();
				set(MENU_MODE);
			}
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
				quit(true);
			}
			break;
		}
	}

}

void reset_last_menu_activity_time() {
	time(&options::last_menu_activity_time);
}

// Callbacks

void menu_autoload(int timer) {
	std::cout << "auto: menu autoload:\n"
		<< "  application mode: " << application.mode << "\n"
		<< "  number to skip: " << timer << "\n"
		<< "  foreword number: " << foreword.times_shown << std::endl;
	if(application.mode == FOREWORD_MODE) {
		if(foreword.times_shown == timer) {
			application.set(MENU_MODE);
		}
	}
}

void screensaver_autoload(int timer) {
	time_t time_left = options::time_to_screensaver();
	if(
		application.mode == MENU_MODE &&
		time_left <= 0
	) {
			std::cout << "auto: screensaver autoload" << std::endl;
			//screensaver.start(options::screensaver_kind);
			screensaver.load(QUEENS_SCREENSAVER);
			application.set(SCREENSAVER_MODE);
	} else {
		glutTimerFunc(10, screensaver_autoload, 0);
	}
}

void auto_exit(int timer) {
	if(application.mode == AFTERWORD_MODE) {
		std::cout << "auto: exit" << std::endl;
		exit(EXIT_SUCCESS);
	}
}
