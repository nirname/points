#pragma once

struct MenuItem;
struct Menu;
struct Interface;

typedef std::list<MenuItem> MenuItems;
typedef std::list<Menu> Menus;

struct MenuItem {

	std::string title;
	Menus::iterator next_menu;

	MenuItem(std::string _title = "") : title(_title) {}

	void handle(unsigned char key, int special_key, Interface * interface, Menu * menu);
	void display(int position);

};


struct Menu {

	std::string title;
	MenuItems items;
	MenuItems::iterator current_item;

	Menu(std::string _title = "") : title(_title) {}

	bool valid();
	MenuItems::iterator add_item(std::string item_title, Menus::iterator);
	void set_current_item(MenuItems::iterator item);
	void handle(unsigned char key, int special_key, Interface * interface);
	void display();

};

struct Interface {

	Menus menus;
	Menus::iterator current_menu;

	Interface() {}

	bool valid();
	Menus::iterator add_menu(std::string menu_title);
	void set_current_menu(Menus::iterator menu);
	void handle(unsigned char key, int special_key);
	void display();
	void load();

};

// MenuItem

void MenuItem::handle(unsigned char key, int special_key, Interface * interface, Menu * menu) {
	if(key == ENTER_KEY) {
		std::cout << " ~ " << title;
		//interface->set_current_menu(next_menu);
	}
}

void MenuItem::display(int position) {
	graphics::write("* " + title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
}

// Menu

bool Menu::valid() {
	return !items.empty() && current_item != items.end();
}

MenuItems::iterator Menu::add_item(std::string item_title, Menus::iterator menu) {
	bool first = items.empty();
	MenuItems::iterator item = items.insert(items.end(), MenuItem(item_title));
	item->next_menu = menu;
	if(first) {
		current_item = item;
	}
	return item;
}

void Menu::set_current_item(MenuItems::iterator item) {
	if(item != items.end()) {
		current_item = item;
	}
}

void Menu::handle(unsigned char key, int special_key, Interface * interface) {
	if(key == ESCAPE_KEY) {
		std::cout << " ~ quit";
		std::cout << std::endl;
		exit(EXIT_SUCCESS);
	} else if(valid()) {
		if(special_key == GLUT_KEY_DOWN) {
			current_item++;
			if(current_item == items.end()) {
				current_item = items.begin();
			}
		} else if(special_key == GLUT_KEY_UP) {
			current_item--;
			if(current_item == items.end()) {
				current_item--;
			}
		} else {
			current_item->handle(key, special_key, interface, this);
		}
	}
	
}

void Menu::display() {
	graphics::write(title);
	if(valid()) {
		int position = 2;
		for(MenuItems::iterator item = items.begin(); item != items.end(); ++item, position += 1) {
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
	Menus::iterator menu = menus.insert(menus.end(), Menu(menu_title));
	if(first) {
		set_current_menu(menu);
	}
	return menu;
}

void Interface::set_current_menu(Menus::iterator menu) {
	if(menu != menus.end()) {
		current_menu = menu;
	}
}

void Interface::handle(unsigned char key, int special_key) {
	if(valid()) {
		current_menu->handle(key, special_key, this);
	}
}

void Interface::display() {
	if(valid()) {
		current_menu->display();
	}
}

void Interface::load() {

	Menus::iterator menu;
	MenuItems::iterator item;

	menu = add_menu("Main menu");
	
	
	menu->add_item("Start", menus.end());
	menu->add_item("Extras", menus.end());
	menu->add_item("Exit", menus.end());

	menu = add_menu("Select game");

	/*menu = add_menu("Extras");
	menu->add_item("Screensavers");
	menu->add_item("Images");*/

};
