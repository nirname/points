#pragma once

#include <ctime>

#include "application_mode.hpp"

struct Application {

	APPLICATION_MODE mode;

	Application();

	void start();
	void quit(bool quit_immidiately = false);

	bool set(APPLICATION_MODE next_mode);

	void handle(unsigned char, int);

};

extern time_t last_menu_activity_time;
void reset_last_menu_activity_time();

void menu_autoload(int timer);
void screensaver_autoload(int timer);
void auto_exit(int timer);
