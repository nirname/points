#include "interface.hpp"

Interface::Interface() {
	loader = NULL;
	displayer = NULL;
	handler = NULL;
}

Interface::Interface(InterfaceLoader _loader) : loader(_loader) {
	displayer = NULL;
	handler = NULL;
	reset_last_activity_time();
}

void Interface::load() {
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
	reset_last_activity_time();
	if(handler != NULL) {
		handler(key, special_key, this);
	}
}

Menus::iterator Interface::add_menu(std::string name) {
	bool is_first = menus.empty();
	Menus::iterator menu = menus.insert(menus.end(), NamedMenu(name, Menu(this)));
	menu->second.title = name;
	if(is_first) {
		forward(menu);
	}
	return menu;
}

void Interface::forward(Menus::iterator menu) {
	if(menu != menus.end()) {
		menus_stack.push_back(menu);
	}
}

void Interface::backward() {
	menus_stack.pop_back();
}

void Interface::reset() {
	menus_stack.clear();
}

void Interface::reset_last_activity_time() {
	time(&last_activity_time);
}

Menus::iterator Interface::current_menu() {
	if(menus_stack.empty()) {
		return menus.end();
	} else {
		return menus_stack.back();
	}
}

Menu::Menu(Interface * _interface) : interface(_interface) {
	current_item = items.end();
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

MenuItems::iterator Menu::add_item(const std::string & name) {
	bool is_first = items.empty();
	MenuItems::iterator item = items.insert(items.end(), MenuItem(this));
	item->title = name;
	if(is_first) {
		current_item = item;
	}
	//item->next_menu = interface->menus.end();
	return item;
}

MenuItem::MenuItem(Menu * _menu) : menu(_menu) {
	next_menu = menu->interface->menus.end();
}

void MenuItem::handle(unsigned char key, int special_key, Interface * interface, Menu * menu) {
	if(handler != NULL) {
		handler(key, special_key, this);
	}
}

void MenuItem::display(int position) {
	if(displayer != NULL) {
		displayer(position, this);
	}
}
