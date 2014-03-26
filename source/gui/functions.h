#pragma once

void quit(unsigned char key, int special_key, MenuItem * menu_item) {
	if(key == ENTER_KEY) {
		application.quit();
	}
}

void display_back_option(int position, MenuItem * _menu_item) {
	graphics::write(" < " + _menu_item->title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
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

void quick_start(unsigned char key, int special_key, MenuItem * _menu_item) {
	std::cout << " -> quick start";
	if(key == ENTER_KEY) {
		application.set(GAMEPLAY_MODE);
	}
}

void start_game(unsigned char key, int special_key, MenuItem * _menu_item) {
	
}

void select_game(unsigned char key, int special_key, MenuItem * _menu_item) {
	if(key == ENTER_KEY) {
		//GAME_KIND _game_kind = NO_GAME;
		//_menu_item->title >> _game_kind;
		std::cout << " -> ";
		_menu_item->next_menu->second.items.clear();
		lines levels;
		std::string path = std::string("levels/") + _menu_item->title;
		if(Directory::read(path, DT_REG, levels)) {
			std::cout << "Levels";
			levels.sort();
			for(lines::iterator level = levels.begin(); level != levels.end(); level++) {
				//std::cout << "\n" << *level << std::ends;
				_menu_item->next_menu->second.add_item(*level, start_game);
			}
		}
		// TODO: remove 'interface' variable from here
		MenuItems::iterator item = _menu_item->next_menu->second.add_item("Back", interface.menus.find("Games"));
		item->displayer = display_back_option;
		//interface->menus["Games"].add_item(lib::to_string(game_kind), GAMEPLAY_MODE);
		//application.set(GAMEPLAY_MODE);
	}
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
	interface->add_menu("Levels");
	//interface->add_menu("Extras");
	interface->add_menu("Screensavers");

	interface->menus["Main menu"].add_item("Play", quick_start);
	interface->menus["Main menu"].add_item("Start", interface->menus.find("Games"));
	//interface->menus["Main menu"].add_item("Extras", interface->menus.find("Extras"));
	interface->menus["Main menu"].add_item("Screensavers", interface->menus.find("Screensavers"));
	item = interface->menus["Main menu"].add_item("Exit", quit);
	item->displayer = display_back_option;

	for(GAME_KIND game_kind = SNAKE; game_kind <= CORNERS; game_kind++) {
		item = interface->menus["Games"].add_item(lib::to_string(game_kind), select_game);
		item->next_menu = interface->menus.find("Levels");
	}
	item = interface->menus["Games"].add_item("Back", interface->menus.find("Main menu"));
	item->displayer = display_back_option;

	/*menus["Extras"].add_item("Screensavers", menus.find("Screensavers"));
	menus["Extras"].add_item("Credits", menus.end());
	menus["Extras"].add_item("Back", menus.find("Main menu"));*/

	for(SCREENSAVER_KIND screensaver_kind = LIFE_SCREENSAVER; screensaver_kind <= TIMER_SCREENSAVER; screensaver_kind++) {
		item = interface->menus["Screensavers"].add_item(lib::to_string(screensaver_kind), start_screensaver);
		item->displayer = display_screensaver_option;
	}
	item = interface->menus["Screensavers"].add_item("Back", interface->menus.find("Main menu"));
	item->displayer = display_back_option;

}

