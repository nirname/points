#pragma once

struct MenuItem;
struct Menu;
struct Interface;

typedef std::list<MenuItem> MenuItems;
typedef std::list<Menu> Menus;

struct MenuItem {

	std::string title;

	MenuItem(std::string _title = "") : title(_title) {}

	void handle(unsigned char key, int special_key) {}

	void display(int position) {
		graphics::write("* " + title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
	}

};

struct Menu {

	std::string title;
	MenuItems items;
	MenuItems::iterator current_item;

	Menu(std::string _title = "") : title(_title) {
	}

	MenuItems::iterator add_item(std::string item_title) {
		return items.insert(items.end(), MenuItem(item_title));
	}

	void set_current_item(MenuItems::iterator item) {
		current_item = item;
	}

	void handle(unsigned char key, int special_key) {
		if(key == ESCAPE_KEY) {
			std::cout << " ~ quit";
			std::cout << std::endl;
			exit(EXIT_SUCCESS);
		} else if(special_key == GLUT_KEY_DOWN || special_key == GLUT_KEY_RIGHT) {
			current_item++;
		} else if(special_key == GLUT_KEY_UP || special_key == GLUT_KEY_LEFT) {
			current_item--;
		} else if(current_item != items.end()) {
			current_item->handle(key, special_key);
		}
	}
	
	void display() {
		
		graphics::write(title);
		
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

};


struct Interface {

	Menus menus;
	Menus::iterator current_menu;

	Interface() {}

	Menus::iterator add_menu(std::string menu_title) {
		return menus.insert(menus.end(), Menu(menu_title));
	}

	void set_current_menu(Menus::iterator menu) {
		current_menu = menu;
		menu->set_current_item(menu->items.begin());
	}

	void handle(unsigned char key, int special_key) {
		if(current_menu != menus.end()) {
			current_menu->handle(key, special_key);
		}
	}

	void display() {
		if(current_menu != menus.end()) {
			current_menu->display();
		}
	}

	void load() {

		Menus::iterator menu;
		MenuItems::iterator item;

		menu = add_menu("Main menu");
		menu->add_item("Start");
		item = menu->add_item("Extras");
		menu->add_item("Exit");

		menu = add_menu("Select game");

		menu = add_menu("Extras");
		menu->add_item("Screensavers");
		menu->add_item("Images");
		
		set_current_menu(menus.begin());

	};

};
