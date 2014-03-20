#pragma once

struct MenuItem;
struct Menu;
struct Interface;

typedef std::list<MenuItem> MenuItems;
typedef std::list<Menu> Menus;

struct MenuItem {

	std::string title;
	MenuItem(std::string _title = "") : title(_title) {
	}

};

struct Menu {

	std::string title;
	MenuItems items;
	MenuItems::iterator current_item;

	Menu(std::string _title = "") : title(_title) {
		current_item = items.begin();
	}

	void next_item() {
		if(!items.empty()) {
			//++current_item;
		}
	}
	
	void previous_item() {
		if(!items.empty()) {
			//--current_item;
		}
	}

	void handle(unsigned char key, int special_key) {
		if(key == ESCAPE_KEY) {
			exit(EXIT_SUCCESS);
		} else if(special_key == GLUT_KEY_DOWN || special_key == GLUT_KEY_RIGHT) {
			next_item();
		} else if(special_key == GLUT_KEY_UP || special_key == GLUT_KEY_LEFT) {
			previous_item();
		}
	}
	
	void display() {
		graphics::write("Menu");
	}

};


struct Interface {

	Menus menus;
	Menus::iterator current_menu;

	Interface() {
		current_menu = menus.begin();
	}

	void load() {};
	
	void display() {
		if(current_menu != menus.end())
			current_menu->display();
	}

	void handle(unsigned char key, int special_key) {
		if(current_menu != menus.end())
			current_menu->handle(key, special_key);

		/*if(key == ESCAPE_KEY) {
			std::cout << ": quit";
			std::cout << std::endl;
			exit(EXIT_SUCCESS);
		} else if(key == ENTER_KEY) {
		}// else {
		//	std::cout << ": free";
		//}
		// TODO: handle all actions to menu
		/*if(key == ESCAPE_KEY) {
			std::cout << ": quit";
			std::cout << std::endl;
			exit(EXIT_SUCCESS);
		} else if(key == ENTER_KEY) {
			//std::cout << ": start";
			//TODO: menu.process(key);
			set(GAMEPLAY_MODE);
		} else if(key == 115 || key == 100) {
			std::cout << ": next item";
			++menu.current_item;
		} else if(key == 119 || key == 97) {
			std::cout << ": previous item";
			--menu.current_item;
		} else {
			std::cout << ": free";
		}*/
	
	}

};
