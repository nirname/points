#ifndef PROGRAM_H
#define PROGRAM_H 1

namespace engine {

	void screensaver_autoload(int);

	struct Program {

		PROGRAM_MODE mode;

		Program() {
			mode = TITRES_MODE;
		}

		// Reset menu activity value on user actions
		void reset_last_activity_time() {
			params::last_menu_activity_time = time(NULL);
		}

		void set(PROGRAM_MODE _mode) {
			reset_last_activity_time();
			if(_mode == MENU_MODE) {
				glutTimerFunc(1000, screensaver_autoload, 0); // TODO: move this one to menu.load() function
				if(game.loaded) {
					game.pause(); // TODO: delete game here
				}
			} else if(_mode == GAMEPLAY_MODE) {
				if(!game.loaded) {
					game.load();
				} else if(game.paused) {
					game.resume();
				}
			} else if(_mode == INFORMATION_MODE) {
				if(game.paused) {
					game.resume();
				}
			}
			mode = _mode;
		}

		void titres_process(unsigned char key) {
			std::cout << ": skip";
			set(MENU_MODE);
		}

		void menu_process(unsigned char key) {

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
				menu.process(key);
				//set(GAMEPLAY_MODE);
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

		void game_process(unsigned char key) {
			if(key == ESCAPE_KEY) {
				std::cout << ": info";
				//set(INFORMATION_MODE);
				set(MENU_MODE);
			} else {
				game.process(key);
				//std::cout << ": free";
			}
		}

		void screensaver_process(unsigned char key) {
			std::cout << ": skip";
			set(MENU_MODE);
		}

		// TODO: void process(int key, int special) {
		void process(unsigned char key) {

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

	};

	void menu_autoload(int timer) {
		if(program.mode == TITRES_MODE) {
			std::cout << "auto: menu autoload" << std::endl;
			program.set(MENU_MODE);
		}
	}

	void screensaver_autoload(int timer) {
		if(program.mode == MENU_MODE) {
			if((time(NULL) - params::last_menu_activity_time) >= params::menu_timeout) {
				std::cout << "auto: screensaver autoload" << std::endl;
				program.set(SCREENSAVER_MODE);
			} else {
				glutTimerFunc(1000, screensaver_autoload, 0); // TODO: move this one to menu.load() function
			}
		}
	}

}

#endif
