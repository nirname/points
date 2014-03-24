#pragma once

struct Interface {

	engine::Application * application;

	Menus menus;
	Menus::iterator current_menu;

	void (* loader)(Interface *);

	Interface(engine::Application * _application, void (* _loader)(Interface *) = NULL):
		application(_application), loader(_loader)
	{}

	bool valid();
	Menus::iterator add_menu(std::string menu_title);
	void set_current_menu(Menus::iterator menu);
	void handle(unsigned char key, int special_key);
	void display();
	void load();

};
