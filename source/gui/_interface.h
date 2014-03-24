#pragma once

struct Interface {

	engine::Application * application;

	Menus menus;
	Menus::iterator current_menu;

	Interface(engine::Application * _application = NULL):
		application(_application)
	{}

	bool valid();
	Menus::iterator add_menu(std::string menu_title);
	void set_current_menu(Menus::iterator menu);
	void handle(unsigned char key, int special_key);
	void display();
	void load();

};
