#pragma once

struct MenuItem {

	std::string title;
	Menus::iterator next_menu;
	MenuItemHandler handler;
	void (*displayer)(int, MenuItem *);

	MenuItem(std::string _title = "") : title(_title) {
		handler = NULL;
		displayer = NULL;
	}

	void handle(unsigned char key, int special_key, Interface * interface, Menu * menu);
	void display(int position);

};
