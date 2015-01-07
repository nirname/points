#include "interface.hpp"

Interface::Interface() {
	displayer = NULL;
	handler = NULL;
}

void Interface::load(InterfaceLoader loader) {
	if(loader != NULL) {
		loader(this);
	}
}

void Interface::display() {
	if(displayer != NULL) {
		displayer(this);
	}
}

void Interface::handle(unsigned char key, int special_key) {
	if(handler != NULL) {
		handler(key, special_key, this);
	}
}

Menu * Interface::add_menu(const std::string & name, MenuDisplayer _displayer, MenuHandler _handler) {
	bool is_first = menus.empty();
	Menus::iterator menu_iterator = menus.insert(menus.end(), Menu(this));
	Menu * menu = &*menu_iterator;
	menu->name = name;
	menu->displayer = _displayer;
	menu->handler = _handler;
	if(is_first) {
		next_menu(menu);
	}
	return menu;
}

Menu * Interface::find_menu(const std::string & name) {
	for(Menus::iterator menu_iterator = menus.begin(); menu_iterator != menus.end(); menu_iterator++) {
		if(menu_iterator->name == name) {
			return &*menu_iterator;
		}
	}
	return NULL;
}

void Interface::next_menu(Menu * menu) {
	if(menu != NULL) {
		menus_stack.push_back(menu);
	}
}

void Interface::previous_menu() {
	menus_stack.pop_back();
}

void Interface::reset() {
	menus_stack.clear();
}

Menu * Interface::current_menu() {
	if(menus_stack.empty()) {
		return NULL;
	} else {
		return menus_stack.back();
	}
}

Menu::Menu(Interface * _interface) : interface(_interface) {
	displayer = NULL;
	handler = NULL;
	_current_item = items.end();
}

void Menu::handle(unsigned char key, int special_key) {
	if(handler != NULL) {
		handler(key, special_key, this);
	}
}

void Menu::display() {
	if(displayer != NULL) {
		displayer(this);
	}
}

MenuItem * Menu::add_item(const std::string & name, MenuItemDisplayer _displayer, MenuItemHandler _handler, Menu * _next_menu) {
	bool is_first = items.empty();
	MenuItems::iterator item_iterator = items.insert(items.end(), MenuItem(this));
	MenuItem * item = &*item_iterator;
	item->name = name;
	item->displayer = _displayer;
	item->handler = _handler;
	item->next_menu = _next_menu;
	if(is_first) {
		_current_item = item_iterator;
	}
	return item;
}

MenuItem * Menu::find_item(const std::string & name) {
	for(MenuItems::iterator item_iterator = items.begin(); item_iterator != items.end(); item_iterator++) {
		if(item_iterator->name == name) {
			return &*item_iterator;
		}
	}
	return NULL;
}

MenuItem * Menu::current_item() {
	if(!items.empty()) {
		if(_current_item != items.end()) {
			return &*_current_item;
		}
	}
	return NULL;
}

void Menu::next_item() {
	if(!items.empty()) {
		_current_item++;
		if(_current_item == items.end()) {
			_current_item++;
		}
	}
}

void Menu::previous_item() {
	if(!items.empty()) {
		_current_item--;
		if(_current_item == items.end()) {
			_current_item--;
		}
	}
}

void Menu::go_to_first() {
	if(!items.empty()) {
		_current_item = items.begin();
	}
}

void Menu::go_to_last() {
	if(!items.empty()) {
		_current_item = --items.end();
	}
}

MenuItem::MenuItem(Menu * _menu) : menu(_menu) {
	displayer = NULL;
	handler = NULL;
	next_menu = NULL;
}

void MenuItem::handle(unsigned char key, int special_key) {
	if(handler != NULL) {
		handler(key, special_key, this);
	}
}

void MenuItem::display() {
	if(displayer != NULL) {
		displayer(this);
	}
}

bool MenuItem::is_current() {
	return menu->current_item() == this;
}
