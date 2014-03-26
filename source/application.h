#pragma once

namespace engine {

	void Application::set(APPLICATION_MODE _mode) {
		APPLICATION_MODE previous_mode = mode;
		mode = LOADING_MODE;
		screen.set(SCREEN_FORMAT_16x9); // TODO: remove
		switch(_mode) {
			case FOREWORD_MODE: {
				glutTimerFunc(options::foreword_timeout * 1000, menu_autoload, 0);
				break;
			}
			case MENU_MODE: {
				reset_last_activity_time();
				glutTimerFunc(options::menu_timeout * 1000, screensaver_autoload, 0);
				if(game.loaded) {
					game.pause();
				}
				break;
			}
			case GAMEPLAY_MODE: {
				screen.set(10, 10);
				if(game.loaded) {
					game.resume();
				} else {
					if(!game.load(NULL)) {
						_mode = previous_mode;
					}
				}
				break;
			}
			case INFORMATION_MODE: {
				if(!game.paused) {
					game.pause();
				}
				break;
			}
			case AFTERWORD_MODE: {
				glutTimerFunc(options::afterword_timeout * 1000, auto_exit, 0); 
				break;
			}
		}
		mode = _mode;
	}

	void Application::handle(unsigned char key, int special_key) {

		std::cout << "key: ";
		printf("%i", key);
		std::cout << ", special key: " << special_key;

		if(key == CTRL_Q_KEY) {
			std::cout << " -> quit" << std::endl;
			exit(EXIT_SUCCESS);
		}

		switch(mode) {
			case LOADING_MODE:         loading_process(key, special_key); break;
			case FOREWORD_MODE:       foreword_process(key, special_key); break;
			case MENU_MODE:               menu_process(key, special_key); break;
			case SCREENSAVER_MODE: screensaver_process(key, special_key); break;
			//case COUNTDOWN_MODE:     countdown_process(key, special_key); break;
			case GAMEPLAY_MODE:       gameplay_process(key, special_key); break;
			//case INFORMATION_MODE: information_process(key, special_key); break;
			case AFTERWORD_MODE:     afterword_process(key, special_key); break;
		}

		std::cout << std::endl;

	}

	void Application::loading_process(unsigned char key, int special_key) {
		// TODO: show a joke or something else
	}

	void Application::foreword_process(unsigned char key, int special_key) {
		set(MENU_MODE);
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
		set(MENU_MODE);
	}
	
	void Application::afterword_process(unsigned char key, int special_key) {
		std::cout << " -> quit" << std::endl;
		exit(EXIT_SUCCESS);
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
			exit(EXIT_SUCCESS);
		}
	}

	// Automatic functions

	void menu_autoload(int timer) {
		if(application.mode == FOREWORD_MODE) {
			std::cout << "auto: menu autoload" << std::endl;
			application.set(MENU_MODE);
		}
	}

	int time_passed(int since) {
		return time(NULL) - since;
	}

	int menu_time_left() {
		return options::menu_timeout - time_passed(options::last_menu_activity_time);
	}

	void screensaver_autoload(int timer) {
		if(application.mode == MENU_MODE) {
			if(menu_time_left() <= 0) {
				std::cout << "auto: screensaver autoload" << std::endl;
				screensaver.kind = options::screensaver_kind;
				application.set(SCREENSAVER_MODE);
			}
			glutTimerFunc(options::menu_timeout * 1000, screensaver_autoload, 0);
		}
	}
	
	void auto_exit(int timer) {
		if(application.mode == AFTERWORD_MODE) {
			std::cout << "auto: exit" << std::endl;
			exit(EXIT_SUCCESS);
		}
	}
	
	void reset_last_activity_time() {
		options::last_menu_activity_time = time(NULL);
	}

}
