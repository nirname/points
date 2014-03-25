#pragma once

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

MenuItems::iterator Menu::add_item(std::string _title, MenuItemHandler _handler) {
	MenuItems::iterator item = add_item(_title);
	item->handler = _handler;
	return item;
}

// TODO: remove it
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
		} else if(key == ESCAPE_KEY) {
			(--items.end())->handle(ENTER_KEY, special_key, interface, this);
		} else {
			current_item->handle(key, special_key, interface, this);
		}
	}
}

void Menu::display(std::string _title) {
	graphics::write(_title);
	if(valid()) {
		int position = 2;
		for(
			MenuItems::iterator item = items.begin();
			item != items.end();
			position += item->indent, ++item
		) {
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
