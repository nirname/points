#pragma once

struct Menu {

	Interface * interface;

	MenuItems items;
	MenuItems::iterator current_item;

	Menu(Interface * _interface = NULL):
		interface(_interface)
	{}

	bool valid();

	MenuItems::iterator add_item(const std::string & _title);
	MenuItems::iterator add_item(const std::string & _title, Menus::iterator _next_menu);
	MenuItems::iterator add_item(const std::string & _title, MenuItemHandler _handler);
	//MenuItems::iterator add_item(std::string _title, APPLICATION_MODE _application_mode);

	void add_indent();

	void set_current_item(MenuItems::iterator item);
	void handle(unsigned char key, int special_key);
	void display(std::string _title);

};
