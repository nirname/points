#pragma once

namespace engine {

	void screensaver_autoload(int);
	void menu_autoload(int);

	struct Application {

		APPLICATION_MODE mode;

		Application() {
			mode == LOADING_MODE;
		}

		void reset_last_activity_time();
		void set(APPLICATION_MODE _mode);

		void process(unsigned char);

		void titres_process(unsigned char);
		void menu_process(unsigned char);
		void game_process(unsigned char);
		void screensaver_process(unsigned char);

	};

	// TODO: move to menu
	// Reset menu activity value on user actions
	void Application::reset_last_activity_time() {
		params::last_menu_activity_time = time(NULL);
	}

	void Application::set(APPLICATION_MODE _mode) {
		glutPostRedisplay();
		reset_last_activity_time(); // TODO: move to menu
		APPLICATION_MODE previous_mode = mode;
		mode = LOADING_MODE;
		if(_mode == TITRES_MODE) {
			screen.set(200, 150);
			// TODO: set to uploaded image size and set background to white
			//opening.open("../images/patterns/ornament/test.bmp");
			//opening.open("fonts/ru.bmp");
			glutTimerFunc(params::titres_timeout * 1000, engine::menu_autoload, 0); // TODO: move it to opening
		} else if(_mode == MENU_MODE) {
			screen.set(200, 150); // TODO: set to what you want
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

	void Application::titres_process(unsigned char key) {
		std::cout << ": skip";
		set(MENU_MODE);
	}

	void Application::menu_process(unsigned char key) {

		// Reset menu activity value on user actions
		//params::last_menu_activity_time = time(NULL);
		reset_last_activity_time();

		// TODO: handle all actions to menu
		if(key == ESCAPE_KEY) {
			std::cout << ": quit";
			std::cout << std::endl;
			exit(EXIT_SUCCESS);
		} else if(key == ENTER_KEY) {
			//std::cout << ": start";
			//TODO: menu.process(key);
			set(GAMEPLAY_MODE);
		} else if(key == 115 || key == 100) {
			std::cout << ": next item";
			++menu.current_item;
		} else if(key == 119 || key == 97) {
			std::cout << ": previous item";
			--menu.current_item;
		} else {
			std::cout << ": free";
		}

	}

	void Application::game_process(unsigned char key) {
		if(key == ESCAPE_KEY) {
			std::cout << ": info";
			//set(INFORMATION_MODE);
			set(MENU_MODE);
		} else {
			game.process(key);
			//std::cout << ": free";
		}
	}

	void Application::screensaver_process(unsigned char key) {
		std::cout << ": skip";
		set(MENU_MODE);
	}

	// TODO: void process(int key, int special) {
	void Application::process(unsigned char key) {

		printf("%i", key);

		if(key == CTRL_Q_KEY) {
			std::cout << ": quit";
			std::cout << std::endl;
			exit(EXIT_SUCCESS);
		}
		if(mode == TITRES_MODE) {
			titres_process(key);
		} else if(mode == MENU_MODE) {
			menu_process(key);
		} else if(mode == SCREENSAVER_MODE) {
			screensaver_process(key);
		} else if(mode == GAMEPLAY_MODE) {
			game_process(key);
		}

		std::cout << std::endl;

	}

	void menu_autoload(int timer) {
		if(application.mode == TITRES_MODE) {
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
