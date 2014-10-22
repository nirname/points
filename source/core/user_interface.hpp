#pragma once

#include "interface.hpp"

struct UI {

	virtual void display_interface(Interface * interface) = 0;
	virtual void display_menu(Menu * menu) = 0;
	virtual void display_menu_item(MenuItem * menu_item) = 0;

	virtual void handle_interface(unsigned char key, int special_key, Interface * interface) = 0;
	virtual void handle_menu(unsigned char key, int special_key, Menu * menu) = 0;
	virtual void handle_menu_item(unsigned char key, int special_key, MenuItem * menu_item) = 0;

};

struct SimpleUI : UI {

	void display_interface(Interface * interface);
	void display_menu(Menu * menu);
	void display_menu_item(MenuItem * menu_item);

	void handle_interface(unsigned char key, int special_key, Interface * interface);
	void handle_menu(unsigned char key, int special_key, Menu * menu);
	void handle_menu_item(unsigned char key, int special_key, MenuItem * menu_item);

};

extern SimpleUI simple_ui;

void load_interface(Interface * interface);
