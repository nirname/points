#pragma once

struct MenuItem {

	int indent;
	std::string title;
	Menus::iterator next_menu;
	MenuItemHandler handler;
	void (*displayer)(int, MenuItem *);

	MenuItem(std::string _title = "", int _indent = 1) :
		title(_title), indent(_indent)
	{
		handler = NULL;
		displayer = NULL;
	}

	void handle(unsigned char key, int special_key, Interface * interface, Menu * menu);
	void display(int position);

};
