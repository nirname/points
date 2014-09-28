#include "application.hpp"

#include <cstdlib>
#include "controls.hpp"

void Application::handle(unsigned char key, int special_key) {

	//std::cout << "key: " << (unsigned int)key << ", special key: " << special_key;

	if(key == CTRL_Q_KEY) {
		//std::cout << " -> quit" << std::endl;
		exit(EXIT_SUCCESS);
	}

/*	switch(mode) {
		case LOADING_MODE:         loading_process(key, special_key); break;
		case FOREWORD_MODE:       foreword_process(key, special_key); break;
		case MENU_MODE:               menu_process(key, special_key); break;
		case SCREENSAVER_MODE: screensaver_process(key, special_key); break;
		//case COUNTDOWN_MODE:     countdown_process(key, special_key); break;
		case GAMEPLAY_MODE:       gameplay_process(key, special_key); break;
		//case INFORMATION_MODE: information_process(key, special_key); break;
		case AFTERWORD_MODE:     afterword_process(key, special_key); break;
	}*/

	//std::cout << std::endl;

}
