#ifndef PROGRAM_H
#define PROGRAM_H 1

namespace engine {

	struct Program {

		PROGRAM_MODE mode;

		Program() {
			mode = TITRES_MODE;
		}

		void set(PROGRAM_MODE _mode) {
			// do something here
			if(_mode == GAMEPLAY_MODE) {
				game.load();
			}
			mode = _mode;

		}

		void titres_process(int key) {
			std::cout << ": skip";
			set(MENU_MODE);
		}

		void menu_process(int key) {
			if(key == ESCAPE_KEY) {
				std::cout << ": quit";
				std::cout << std::endl;
				exit(EXIT_SUCCESS);
			} else if(key == ENTER_KEY) {
				std::cout << ": start";
				set(GAMEPLAY_MODE);
			} else {
				std::cout << ": free";
			}
		}

		void game_process(int key) {
			if(key == ESCAPE_KEY) {
				std::cout << ": info";
				set(INFORMATION_MODE);
			} else {
				std::cout << ": free";
			}
		}

		void information_process(int key) {
			if(key == ESCAPE_KEY) {
				std::cout << ": resume";
				set(GAMEPLAY_MODE);
			} else {
				std::cout << ": free";
			}
		}

		void process(int key) {

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
			} else if(mode == GAMEPLAY_MODE) {
				game_process(key);
			} else if(mode == INFORMATION_MODE) {
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
		std::cout << "auto: screensaver autoload" << std::endl;
	}

}

#endif
