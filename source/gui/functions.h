#pragma once

void quit(MenuItem * menu_item) {
	std::cout << " -> quit" << std::endl;
	exit(EXIT_SUCCESS);
}

void display_option(int position, MenuItem * _menu_item) {
	graphics::write(" (option) * " + _menu_item->title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
}

void start_game(MenuItem * _menu_item) {
	//interface->menus["Games"].add_item(lib::to_string(game_kind), GAMEPLAY_MODE);
	//application.set(GAMEPLAY_MODE);
}

void start_screensaver(MenuItem * _menu_item) {
	_menu_item->title >> screensaver.kind;
	application.set(SCREENSAVER_MODE);
}

namespace gui {

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
		interface->menus["Main menu"].add_indent();
		interface->menus["Main menu"].add_item("Exit", quit);

		for(GAME_KIND game_kind = SNAKE; game_kind <= CORNERS; game_kind++) {
			interface->menus["Games"].add_item(lib::to_string(game_kind), start_game);
		}
		interface->menus["Games"].add_indent();
		interface->menus["Games"].add_item("Back", interface->menus.find("Main menu"));

		/*menus["Extras"].add_item("Screensavers", menus.find("Screensavers"));
		menus["Extras"].add_item("Credits", menus.end());
		menus["Extras"].add_indent();
		menus["Extras"].add_item("Back", menus.find("Main menu"));*/

		for(SCREENSAVER_KIND screensaver_kind = LIFE_SCREENSAVER; screensaver_kind <= TIMER_SCREENSAVER; screensaver_kind++) {
			item = interface->menus["Screensavers"].add_item(lib::to_string(screensaver_kind), start_screensaver);
			item->displayer = display_option;
		}
		interface->menus["Screensavers"].add_indent();
		interface->menus["Screensavers"].add_item("Back", interface->menus.find("Main menu"));

	}

	
}
