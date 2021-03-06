#pragma once

#include <string>
#include <map>
#include <list>
#include <deque>

struct Interface;
struct Menu;
struct MenuItem;

typedef std::list<Menu> Menus;
typedef std::list<MenuItem> MenuItems;

typedef void (* InterfaceLoader)(Interface *);
typedef void (* InterfaceDisplayer)(Interface *);
typedef void (* InterfaceHandler)(unsigned char key, int special_key, Interface *);

typedef void (* MenuDisplayer)(Menu *);
typedef void (* MenuHandler)(unsigned char key, int special_key, Menu *);

typedef void (* MenuItemDisplayer)(MenuItem *);
typedef void (* MenuItemHandler)(unsigned char key, int special_key, MenuItem *);

void next_menu(unsigned char key, int special_key, MenuItem * menu_item);
void back(unsigned char key, int special_key, MenuItem * menu_item);
void back(unsigned char key, int special_key, Interface * interface);

struct Interface {

	Menus menus;
	std::deque< Menu * > menus_stack;

	InterfaceDisplayer displayer;
	InterfaceHandler handler;

	Interface();

	void load(InterfaceLoader loader);
	void display();
	void handle(unsigned char key, int special_key);

	Menu * add_menu(const std::string & name, MenuDisplayer _displayer = NULL, MenuHandler _handler = NULL);
	Menu * find_menu(const std::string & name);

	void next_menu(Menu * menu);
	void previous_menu();
	void back();
	void reset();

	Menu * current_menu();

};

struct Menu {

	Interface * interface;
	std::string name;

	std::string text;

	MenuItems items;
	MenuItems::iterator _current_item;

	MenuDisplayer displayer;
	MenuHandler handler;

	Menu(Interface * _interface);

	void display();
	void handle(unsigned char key, int special_key);

	MenuItem * add_item(
		const std::string & name,
		MenuItemDisplayer _displayer = NULL, MenuItemHandler _handler = NULL,
		Menu * _next_menu = NULL
	);

	Menu * add_menu (
		const std::string & name,
		MenuItemDisplayer _item_displayer = NULL, MenuItemHandler _item_handler = NULL,
		MenuDisplayer _menu_displayer = NULL, MenuHandler _menu_handler = NULL
	);

	MenuItem * find_item(const std::string & name);

	void next_item();
	void previous_item();

	void go_to_first();
	void go_to_last();

	MenuItem * current_item();

};

#include "screensaver_kind.hpp"
#include "game_kind.hpp"

struct MenuItemOptions {

	SCREENSAVER_KIND screensaver_kind;
	GAME_KIND game_kind;
	std::string path;

};

struct MenuItem {

	Menu * menu;
	std::string name;

	Menu * next_menu;

	MenuItemOptions options;

	MenuItemHandler handler;
	MenuItemDisplayer displayer;

	MenuItem(Menu * _menu);

	void handle(unsigned char key, int special_key);
	void display();

	bool is_current();

};
