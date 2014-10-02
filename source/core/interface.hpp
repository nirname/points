#pragma once

#include <string>
#include <map>
#include <list>
#include <deque>
#include <ctime>

struct Interface;
struct Menu;
struct MenuItem;

typedef std::map<std::string, Menu> Menus;
typedef std::pair<std::string, Menu> NamedMenu;

typedef std::map<std::string, MenuItem> MenuItems;
typedef std::pair<std::string, MenuItem> NamedMenuItem;

typedef void (* InterfaceLoader)(Interface *);
typedef void (* InterfaceDisplayer)(Interface *);
typedef void (* InterfaceHandler)(unsigned char key, int special, Interface *);

typedef void (* MenuDisplayer)(Menu *);
typedef void (* MenuHandler)(unsigned char key, int special, Menu *);

typedef void (* MenuItemDisplayer)(int position, MenuItem *);
typedef void (* MenuItemHandler)(unsigned char key, int special, MenuItem *);

struct Interface {

	//time_t last_activity_time;

	Menus menus;
	std::deque< Menus::iterator > menus_stack;

	InterfaceLoader loader;
	InterfaceDisplayer displayer;
	InterfaceHandler handler;

	Interface();
	Interface(InterfaceLoader _loader);

	void load();
	void display();
	void handle(unsigned char key, int special_key);

	Menus::iterator add_menu(std::string name);

	void forward(Menus::iterator menu);
	void backward();
	void reset();

	Menus::iterator current_menu();

};

struct Menu {

	Interface * interface;
	std::string title;

	MenuItems items;
	MenuItems::iterator current_item;

	MenuDisplayer displayer;
	MenuHandler handler;

	Menu(Interface * _interface);

	void display();
	void handle(unsigned char key, int special_key);

	MenuItems::iterator add_item(const std::string & name);

	void set_current_item(MenuItems::iterator item);

};

struct MenuItem {

	Menu * menu;
	std::string title;

	Menus::iterator next_menu;

	MenuItemHandler handler;
	MenuItemDisplayer displayer;

	MenuItem(Menu * _menu);

	void handle(unsigned char key, int special_key, Interface * interface, Menu * menu);
	void display(int position);

};
