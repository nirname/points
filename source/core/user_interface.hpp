#pragma once

#include <iostream>

#include "interface.hpp"
#include "drawing.hpp"
#include "options.hpp"

namespace ui {
	namespace simple {}
}

//void interface_handler() {};

void display_menu(Menu * menu) {

	write(menu->title);

	int position = 1;

	for(MenuItems::iterator item =
		menu->items.begin();
		item != menu->items.end();
		++item, ++position
	) {
		if(item == menu->current_item) {
			glPushAttrib(GL_CURRENT_BIT);
				options::selection_color.use();
				item->display(position);
				write(item->title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
			glPopAttrib();
		} else {
			write(item->title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
		}
	}

}

void display_interface(Interface * interface) {

	Menus::iterator menu;
	MenuItems::iterator item;

	//display_menu(&interface->current_menu()->second);
	//write(menu->second.title);
	/*for(menu = interface->menus.begin(); menu != interface->menus.end(); ++menu) {
		write(menu->second.title);
		for(item = menu->second.items.begin(); item != menu->second.items.end(); ++item) {
			write(item->title);
		}
	}*/

}

void load_interface(Interface * interface) {
	std::cout << "Interface loading" << std::endl;

	Menus::iterator menu;
	MenuItems::iterator item;

	menu = interface->add_menu("Main menu");
	item = menu->second.add_item("Start");
	item = menu->second.add_item("Exit");

	for(menu = interface->menus.begin(); menu != interface->menus.end(); ++menu) {
		std::cout << "  " << menu->second.title << std::endl;
		for(item = menu->second.items.begin(); item != menu->second.items.end(); ++item) {
			std::cout << "    " << item->title << std::endl;
		}
	}
	std::cout << "ok" << std::endl;

	interface->displayer = display_interface;
	//interface.handler = interface_handler;

}
