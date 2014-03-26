#pragma once

void quit(unsigned char key, int special_key, MenuItem * menu_item) {
	std::cout << " -> quit" << std::endl;
	exit(EXIT_SUCCESS);
}

void display_screensaver_option(int position, MenuItem * _menu_item) {

	SCREENSAVER_KIND _screensaver_kind = NO_SCREENSAVER;
	_menu_item->title >> _screensaver_kind;

	std::string title = std::string(" * ") + _menu_item->title;
	title.resize(25, ' ');

	if(_screensaver_kind & options::screensaver_kind) {
		title += "[   ][ON]";
	} else {
		title += "[OFF][  ]";
	}

	graphics::write(title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));

}

void start_game(unsigned char key, int special_key, MenuItem * _menu_item) {
	//interface->menus["Games"].add_item(lib::to_string(game_kind), GAMEPLAY_MODE);
	//application.set(GAMEPLAY_MODE);
}

void start_screensaver(unsigned char key, int special_key, MenuItem * _menu_item) {
	SCREENSAVER_KIND _screensaver_kind = NO_SCREENSAVER;
	_menu_item->title >> _screensaver_kind;
	if(key == ENTER_KEY) {
		screensaver.kind = _screensaver_kind;
		application.set(SCREENSAVER_MODE);
	} else if(special_key == GLUT_KEY_LEFT) {
		options::screensaver_kind = SCREENSAVER_KIND(options::screensaver_kind & ~_screensaver_kind);
	} else if(special_key == GLUT_KEY_RIGHT) {
		options::screensaver_kind = SCREENSAVER_KIND(options::screensaver_kind | _screensaver_kind);
	}
}

void loader(Interface * interface) {

	//Menus::iterator menu;
	MenuItems::iterator item;

	interface->add_menu("Main menu");
	interface->add_menu("Games");
	//interface->add_menu("Extras");
	interface->add_menu("Screensavers");

	interface->menus["Main menu"].add_item("Start", interface->menus.find("Games"));
	//interface->menus["Main menu"].add_item("Extras", interface->menus.find("Extras"));
	interface->menus["Main menu"].add_item("Screensavers", interface->menus.find("Screensavers"));
	interface->menus["Main menu"].add_item("Exit", quit);

	for(GAME_KIND game_kind = SNAKE; game_kind <= CORNERS; game_kind++) {
		interface->menus["Games"].add_item(lib::to_string(game_kind), start_game);
	}
	interface->menus["Games"].add_item("Back", interface->menus.find("Main menu"));

	/*menus["Extras"].add_item("Screensavers", menus.find("Screensavers"));
	menus["Extras"].add_item("Credits", menus.end());
	menus["Extras"].add_item("Back", menus.find("Main menu"));*/

	for(SCREENSAVER_KIND screensaver_kind = LIFE_SCREENSAVER; screensaver_kind <= TIMER_SCREENSAVER; screensaver_kind++) {
		item = interface->menus["Screensavers"].add_item(lib::to_string(screensaver_kind), start_screensaver);
		item->displayer = display_screensaver_option;
	}
	interface->menus["Screensavers"].add_item("Back", interface->menus.find("Main menu"));

}

