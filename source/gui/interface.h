#pragma once

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
	if(loader != NULL) {
		loader(this);
	}
}

