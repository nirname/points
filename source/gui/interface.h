#pragma once

bool Interface::valid() {
	return !menus.empty() && current_menu != menus.end();
}

Menus::iterator Interface::add_menu(std::string menu_title) {
	bool first = menus.empty();
	std::pair<Menus::iterator, bool> result = menus.insert(MenuWithTitle(menu_title, Menu(this)));
	if(result.second) {
		if(first) {
			set_current_menu(result.first);
		}
	}
	return result.first;
}

void Interface::set_current_menu(Menus::iterator menu) {
	if(menu != menus.end()) {
		current_menu = menu;
		current_menu->second.set_current_item(current_menu->second.items.begin());
	}
}

void Interface::handle(unsigned char key, int special_key) {
	if(valid()) {
		current_menu->second.handle(key, special_key);
	}
}

void Interface::display() {
	if(valid()) {
		current_menu->second.display(current_menu->first);
	}
}

void Interface::load() {

	//Menus::iterator menu;
	MenuItems::iterator item;

	add_menu("Main menu");
	add_menu("Games");
	add_menu("Extras");
	add_menu("Screensavers");

	menus["Main menu"].add_item("Start", menus.find("Games"));
	//menus["Main menu"].add_item("Extras", menus.find("Extras"));
	menus["Main menu"].add_item("Screensavers", menus.find("Screensavers"));
	menus["Main menu"].add_indent();
	menus["Main menu"].add_item("Exit", quit);

	for(GAME_KIND game_kind = SNAKE; game_kind <= CORNERS; game_kind++) {
		menus["Games"].add_item(lib::to_string(game_kind), GAMEPLAY_MODE);
	}
	menus["Games"].add_indent();
	menus["Games"].add_item("Back", menus.find("Main menu"));

	/*menus["Extras"].add_item("Screensavers", menus.find("Screensavers"));
	menus["Extras"].add_item("Credits", menus.end());
	menus["Extras"].add_indent();
	menus["Extras"].add_item("Back", menus.find("Main menu"));*/

	for(SCREENSAVER_KIND screensaver_kind = LIFE_SCREENSAVER; screensaver_kind <= TIMER_SCREENSAVER; screensaver_kind++) {
		item = menus["Screensavers"].add_item(lib::to_string(screensaver_kind), SCREENSAVER_MODE);
		item->custom_display = display_option;
	}
	menus["Screensavers"].add_indent();
	menus["Screensavers"].add_item("Back", menus.find("Main menu"));

};

