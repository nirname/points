#pragma once

struct MenuItem {

	int indent;
	std::string title;
	Menus::iterator next_menu;
	APPLICATION_MODE next_mode;
	void (*handler)();
	void (*custom_display)(int, MenuItem *);

	MenuItem(std::string _title = "", int _indent = 1) :
		title(_title), indent(_indent)
	{
		handler = NULL;
		custom_display = NULL;
		next_mode = MENU_MODE;
	}

	void handle(unsigned char key, int special_key, Interface * interface, Menu * menu);
	void display(int position);

};
