#include "user_interface.hpp"

#include <iostream>

#include "drawing.hpp"
#include "options.hpp"
#include "opengl.hpp"

SimpleUI simple_ui;

void SimpleUI::display_interface(Interface * interface) {
	display_menu(&(interface->current_menu()->second));
}

void SimpleUI::display_menu(Menu * menu) {
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
				write(item->title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
			glPopAttrib();
		} else {
			write(item->title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
		}
	}
}

void SimpleUI::display_menu_item(MenuItem * menu_item) {
	//write(item->title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
};

void SimpleUI::handle_interface(unsigned char key, int special_key, Interface * interface) {
	Menu * menu = &(interface->current_menu()->second);
	handle_menu(key, special_key, menu);
}

void SimpleUI::handle_menu(unsigned char key, int special_key, Menu * menu) {
	if(special_key == GLUT_KEY_DOWN) {
		menu->current_item++;
		if(menu->current_item == menu->items.end()) {
			menu->current_item++;
		}
	} else if(special_key == GLUT_KEY_UP) {
		menu->current_item--;
		if(menu->current_item == menu->items.end()) {
			menu->current_item--;
		}
	} else if(special_key == GLUT_KEY_END) {
		menu->current_item = --menu->items.end();
	} else if(special_key == GLUT_KEY_HOME) {
		menu->current_item = menu->items.begin();
	} else {
		menu->current_item->handle(key, special_key);
	}
}

void SimpleUI::handle_menu_item(unsigned char key, int special_key, MenuItem * menu_item) {
};

void load_interface(Interface * interface) {
	std::cout << "Interface loading" << std::endl;

	interface->add_menu("Main menu");
	interface->add_menu("Games");
	interface->add_menu("Extras");

	/*Menus::iterator menu;
	MenuItems::iterator item;

	interface->add_menu("Levels");
	interface->add_menu("Screensavers");

	interface->menus["Main menu"].add_item("Play!", quick_start);
	interface->menus["Main menu"].add_item("Start", interface->menus.find("Games"));
	interface->menus["Main menu"].add_item("Extras", interface->menus.find("Extras"));
	interface->menus["Main menu"].add_item("Screensavers", interface->menus.find("Screensavers"));
	item = interface->menus["Main menu"].add_item("Exit", quit);
	item->displayer = display_back_option;

	for(GAME_KIND game_kind = SNAKE; game_kind <= CORNERS; game_kind++) {
		item = interface->menus["Games"].add_item(lib::to_string(game_kind), select_game);
		item->next_menu = interface->menus.find("Levels");
	}
	item = interface->menus["Games"].add_item("Back", interface->menus.find("Main menu"));
	item->displayer = display_back_option;

	menus["Extras"].add_item("Screensavers", menus.find("Screensavers"));
	menus["Extras"].add_item("Credits", menus.end());
	menus["Extras"].add_item("Back", menus.find("Main menu"));

	for ( SCREENSAVER_KIND
		screensaver_kind = LIFE_SCREENSAVER;
		screensaver_kind <= TIMER_SCREENSAVER;
		screensaver_kind++
	) {
		item = interface->menus["Screensavers"].add_item(
			lib::to_string(screensaver_kind),
			start_screensaver
		);
		item->displayer = display_screensaver_option;
	}
	item = interface->menus["Screensavers"].add_item("Back", interface->menus.find("Main menu"));
	item->displayer = display_back_option;*/

	Menus::iterator menu_iterator;
	//MenuItems::iterator item_iterator;

	Menu * menu = NULL;
	//MenuItem * item = NULL;

	interface->add_menu("Main menu");
	interface->add_menu("Previous menu");

	menu = &interface->menus.find("Main menu")->second;
	menu->add_item("Start");
	menu->add_item("Exit");

	/*for(menu_iterator = interface->menus.begin(); menu_iterator != interface->menus.end(); ++menu_iterator) {
		std::cout << "  " << menu_iterator->second.title << std::endl;

		for(item_iterator = menu->second.item_iterator.begin(); item != menu->second.items.end(); ++item) {
			std::cout << "    " << item->title << std::endl;
		}
	}*/
	std::cout << "ok" << std::endl;

	//interface->displayer = display_interface;
	//interface->handler = handle_interface;

	//std::cout << &(interface->current_menu()->second) << std::endl;

}

/*
void quit(unsigned char key, int special_key, MenuItem * menu_item) {
	if(key == ENTER_KEY) {
		application.quit();
	}
}

void display_back_option(int position, MenuItem * _menu_item) {
	graphics::write(" < " + _menu_item->title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
}

void display_screensaver_option(int position, MenuItem * _menu_item) {

	SCREENSAVER_KIND _screensaver_kind = NO_SCREENSAVER;
	_menu_item->title >> _screensaver_kind;

	std::string title = std::string(" * ") + _menu_item->title;
	title.resize(25, ' ');

	if(_screensaver_kind & options::screensaver_kind) {
		title += "[   ][ON]";
	} else {
		title += "[OFF][  ]";
	}

	graphics::write(title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));

}

void quick_start(unsigned char key, int special_key, MenuItem * _menu_item) {
	if(key == ENTER_KEY) {
		game.kind = SOKOBAN;
		game.load("levels/Sokoban/Level-1.yaml");
		application.set(GAMEPLAY_MODE);
	}
}

void start_game(unsigned char key, int special_key, MenuItem * _menu_item) {
	if(key == ENTER_KEY) {
		game.load("levels/" + lib::to_string(game.kind) + "/" + _menu_item->title);
		application.set(GAMEPLAY_MODE);
	}
}

void select_game(unsigned char key, int special_key, MenuItem * _menu_item) {
	if(key == ENTER_KEY) {
		std::cout << " -> ";
		_menu_item->next_menu->second.items.clear();
		lines levels;
		std::string path = std::string("levels/") + _menu_item->title;
		if(Directory::read(path, DT_REG, levels)) {
			std::cout << "Levels";
			levels.sort();
			if(!levels.empty()) {
				_menu_item->title >> game.kind;
				for(lines::iterator level = levels.begin(); level != levels.end(); level++) {
					//std::cout << "\n" << *level << std::ends;
					_menu_item->next_menu->second.add_item(*level, start_game);
				}
				//GAME_KIND _game_kind = NO_GAME;
				//_menu_item->title >> _game_kind;
			}
		}
		// TODO: remove 'interface' variable from here
		MenuItems::iterator item = _menu_item->next_menu->second.add_item(
			"Back",
			interface.menus.find("Games")
		);
		item->displayer = display_back_option;
		//interface->menus["Games"].add_item(lib::to_string(game_kind), GAMEPLAY_MODE);
		//application.set(GAMEPLAY_MODE);
	}
}

void start_screensaver(unsigned char key, int special_key, MenuItem * _menu_item) {
	SCREENSAVER_KIND _screensaver_kind = NO_SCREENSAVER;
	_menu_item->title >> _screensaver_kind;
	if(key == ENTER_KEY) {
		screensaver.kind = _screensaver_kind;
		application.set(SCREENSAVER_MODE);
	} else if(special_key == GLUT_KEY_LEFT) {
		options::screensaver_kind = SCREENSAVER_KIND (
			options::screensaver_kind & ~_screensaver_kind
		);
	} else if(special_key == GLUT_KEY_RIGHT) {
		options::screensaver_kind = SCREENSAVER_KIND (
			options::screensaver_kind | _screensaver_kind
		);
	}
}
*/
