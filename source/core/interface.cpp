#include "interface.hpp"

Interface::Interface() {
	loader = NULL;
	displayer = NULL;
	handler = NULL;
}

Interface::Interface(InterfaceLoader _loader) : loader(_loader) {
	displayer = NULL;
	handler = NULL;
	//reset_last_activity_time();
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
	if(handler != NULL) {
		handler(key, special_key, this);
	}
}

Menus::iterator Interface::add_menu(std::string name) {
	bool is_first = menus.empty();
	std::pair<Menus::iterator, bool> result = menus.insert(NamedMenu(name, Menu(this)));
	if(result.second) {
		if(is_first) {
			forward(result.first);
		}
	}
	return result.first;
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
