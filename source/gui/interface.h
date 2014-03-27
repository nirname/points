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
		if(current_menu->second.current_item == --(current_menu->second.items.end())) {
			current_menu->second.set_current_item(current_menu->second.items.begin());
		}
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
	if(options::screensaver_kind != NO_SCREENSAVER) {
		graphics::write(lib::to_string(engine::menu_time_left()), 200, 0);
	}
	graphics::square();
}

void Interface::load() {
	std::cout << "Loading interface: " << std::ends;
	if(loader != NULL) {
		loader(this);
	}
	std::cout << "Yes" << std::endl;
}

