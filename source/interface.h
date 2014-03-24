#pragma once

void quit();

struct MenuItem;
struct Menu;
struct Interface;

typedef std::pair<std::string, Menu> MenuWithTitle;

typedef std::list<MenuItem> MenuItems;
typedef std::map<std::string, Menu> Menus;

struct MenuItem {

	int indent;
	std::string title;
	Menus::iterator next_menu;
	APPLICATION_MODE next_mode;
	void (*handler)();

	MenuItem(std::string _title = "", int _indent = 1) :
		title(_title), indent(_indent)
	{
		handler = NULL;
		next_mode = MENU_MODE;
	}

	void handle(unsigned char key, int special_key, Interface * interface, Menu * menu);
	void display(int position);

};


struct Menu {

	Interface * interface;

	MenuItems items;
	MenuItems::iterator current_item;

	Menu(Interface * _interface = NULL):
		interface(_interface)
	{}

	bool valid();

	MenuItems::iterator add_item(std::string item_title);
	MenuItems::iterator add_item(std::string item_title, Menus::iterator menu);
	MenuItems::iterator add_item(std::string item_title, void(*_handler)());
	MenuItems::iterator add_item(std::string _title, APPLICATION_MODE _application_mode);

	void add_indent();

	void set_current_item(MenuItems::iterator item);
	void handle(unsigned char key, int special_key);
	void display(std::string _title);

};

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

// MenuItem

void MenuItem::handle(unsigned char key, int special_key, Interface * interface, Menu * menu) {
	std::cout << " ~ " << title;
	if(key == ENTER_KEY) {
		if(next_menu != interface->menus.end()) {
			interface->set_current_menu(next_menu);
		}
		if(handler != NULL) {
			handler();
		} else {
			interface->application->set(next_mode);
		}
	}
}

void MenuItem::display(int position) {
	graphics::write(" * " + title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
}

// Menu

bool Menu::valid() {
	return !items.empty() && current_item != items.end();
}

MenuItems::iterator Menu::add_item(std::string _title) {
	bool first = items.empty();
	MenuItems::iterator item = items.insert(items.end(), MenuItem(_title));
	if(first) {
		current_item = item;
	}
	item->next_menu = interface->menus.end();
	return item;
}

MenuItems::iterator Menu::add_item(std::string _title, Menus::iterator _next_menu) {
	MenuItems::iterator item = add_item(_title);
	item->next_menu = _next_menu;
	return item;
}

MenuItems::iterator Menu::add_item(std::string _title, void(*_handler)()) {
	MenuItems::iterator item = add_item(_title);
	item->handler = _handler;
	return item;
}

MenuItems::iterator Menu::add_item(std::string _title, APPLICATION_MODE _application_mode) {
	MenuItems::iterator item = add_item(_title);
	item->next_mode = _application_mode;
	return item;
}

void Menu::add_indent() {
	items.back().indent += 1;
}

void Menu::set_current_item(MenuItems::iterator item) {
	if(item != items.end()) {
		current_item = item;
	}
}

void Menu::handle(unsigned char key, int special_key) {
	if(valid()) {
		if(special_key == GLUT_KEY_DOWN) {
			current_item++;
			if(current_item == items.end()) {
				current_item = items.begin(); // current_item ++
			}
		} else if(special_key == GLUT_KEY_UP) {
			current_item--;
			if(current_item == items.end()) {
				current_item--;
			}
		} else if(special_key == GLUT_KEY_END) {
			current_item = --items.end();
		} else if(special_key == GLUT_KEY_HOME) {
			current_item = items.begin();
		} else {
			current_item->handle(key, special_key, interface, this);
		}
	}
	
}

void Menu::display(std::string _title) {
	graphics::write(_title);
	if(valid()) {
		int position = 2;
		for(MenuItems::iterator item = items.begin(); item != items.end(); position += item->indent, ++item) {
			if(item == current_item) {
				glPushAttrib(GL_CURRENT_BIT);
					glColor3ub(BLUE);
					item->display(position);
				glPopAttrib();
			} else {
				item->display(position);
			}
		}
	}
}

// Interface

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

	Menus::iterator menu;
	MenuItems::iterator item;

	add_menu("Main menu");
	add_menu("Games");
	add_menu("Extras");
	add_menu("Screensavers");

	menus["Main menu"].add_item("Start", menus.find("Games"));
	menus["Main menu"].add_item("Extras", menus.find("Extras"));
	menus["Main menu"].add_indent();
	menus["Main menu"].add_item("Exit", quit);

	for(GAME_KIND game_kind = SNAKE; game_kind <= CORNERS; game_kind++) {
		menus["Games"].add_item(lib::to_string(game_kind), GAMEPLAY_MODE);
	}
	menus["Games"].add_indent();
	menus["Games"].add_item("Back", menus.find("Main menu"));

	menus["Extras"].add_item("Screensavers", menus.find("Screensavers"));
	menus["Extras"].add_item("Credits", menus.end());
	menus["Extras"].add_indent();
	menus["Extras"].add_item("Back", menus.find("Main menu"));
	

	for(SCREENSAVER_KIND screensaver_kind = BLANK_SCREEN_SCREENSAVER; screensaver_kind <= TIMER_SCREENSAVER; screensaver_kind++) {
		menus["Screensavers"].add_item(lib::to_string(screensaver_kind), SCREENSAVER_MODE);
	}
	menus["Screensavers"].add_indent();
	menus["Screensavers"].add_item("Back", menus.find("Extras"));

};

void quit() {
	std::cout << " -> quit";
	std::cout << std::endl;
	exit(EXIT_SUCCESS);
}
