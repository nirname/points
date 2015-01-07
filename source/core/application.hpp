#pragma once

#include <ctime>

enum APPLICATION_MODE {
	LOADING_MODE,
	FOREWORD_MODE,
	MENU_MODE,
	SCREENSAVER_MODE,
	COUNTDOWN_MODE,
	GAMEPLAY_MODE,
	INFORMATION_MODE,
	AFTERWORD_MODE
};

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
