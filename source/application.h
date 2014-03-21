#pragma once

namespace engine {

	void screensaver_autoload(int);
	void menu_autoload(int);

	struct Application {

		APPLICATION_MODE mode;

		Application() {
			mode == LOADING_MODE;
		}

		void set(APPLICATION_MODE _mode);
		void reset_last_activity_time();

		void handle(unsigned char, int);

		void loading_process(unsigned char);
		void foreword_process(unsigned char);
		void menu_process(unsigned char, int);
		void screensaver_process(unsigned char);
		void countdown_process(unsigned char);
		void gameplay_process(unsigned char);
		void information_process(unsigned char);
		void afterword_process(unsigned char);

	};

	void Application::set(APPLICATION_MODE _mode) {
		glutPostRedisplay();
		reset_last_activity_time(); // TODO: move to menu
		APPLICATION_MODE previous_mode = mode;
		mode = LOADING_MODE;
		if(_mode == FOREWORD_MODE) {
			//screen.set(160, 90);
			// TODO: set to uploaded image size and set background to white
			glutTimerFunc(params::titres_timeout * 1000, engine::menu_autoload, 0); // TODO: move it to opening
		} else if(_mode == MENU_MODE) {
			//screen.set(320, 240); // TODO: set to what you want
			glutTimerFunc(1000, screensaver_autoload, 0); // TODO: move this one to menu.load() function
			if(game.loaded) {
				game.pause(); // TODO: delete game here
			}
		} else if(_mode == GAMEPLAY_MODE) {
			if(!game.load(NULL)) { // TODO: set level here
				mode = previous_mode;
				return;
			}
		} else if(_mode == INFORMATION_MODE) {
			if(game.paused) {
				game.resume();
			}
		}
		mode = _mode;
	}

	void Application::handle(unsigned char key, int special_key) {

		std::cout << "key: ";
		printf("%i", key);
		std::cout << ", special key: " << special_key;

		if(key == CTRL_Q_KEY) {
			std::cout << " ~ quit";
			std::cout << std::endl;
			exit(EXIT_SUCCESS);
		}

		switch(mode) {
			//case LOADING_MODE:         loading_process(key); break;
			case FOREWORD_MODE:       foreword_process(key); break;
			case MENU_MODE:               menu_process(key, special_key); break;
			case SCREENSAVER_MODE: screensaver_process(key); break;
			//case COUNTDOWN_MODE:     countdown_process(key); break;
			case GAMEPLAY_MODE:       gameplay_process(key); break;
			//case INFORMATION_MODE: information_process(key); break;
			//case AFTERWORD_MODE:     afterword_process(key); break;
		}

		std::cout << std::endl;

	}

	void Application::foreword_process(unsigned char key) {
		set(MENU_MODE);
	}

	void Application::menu_process(unsigned char key, int special_key) {
		reset_last_activity_time();
		interface.handle(key, special_key);
	}

	void Application::gameplay_process(unsigned char key) {
		if(key == ESCAPE_KEY) {
			set(MENU_MODE);
		} else {
			game.process(key);
		}
	}

	void Application::screensaver_process(unsigned char key) {
		set(MENU_MODE);
	}

	// TODO: move to menu
	// Reset menu activity value on user actions
	void Application::reset_last_activity_time() {
		params::last_menu_activity_time = time(NULL);
	}


	void menu_autoload(int timer) {
		if(application.mode == FOREWORD_MODE) {
			std::cout << "auto: menu autoload" << std::endl;
			application.set(MENU_MODE);
		}
	}

	void screensaver_autoload(int timer) {
		if(application.mode == MENU_MODE) {
			if((time(NULL) - params::last_menu_activity_time) >= params::menu_timeout) {
				std::cout << "auto: screensaver autoload" << std::endl;
				application.set(SCREENSAVER_MODE);
			} else {
				glutTimerFunc(1000, screensaver_autoload, 0); // TODO: move this one to menu.load() function
			}
		}
	}

}
