#include "user_interface.hpp"

#include <iostream>

#include "drawing.hpp"
#include "options.hpp"
#include "opengl.hpp"
#include "variables.hpp"
#include "library.hpp"

#include "shape.hpp"
#include "controls.hpp"
#include "emitter.hpp"

#include "directory.hpp"
#include "file.hpp"

//std::map<MenuItem *, MenuItemOptions> menu_items_options;

int value_shift = 22;

void display_inline_menu(Interface * interface) {
	if(interface->menus_stack.size() > 1) {
		if(interface->current_menu()->name != std::string("Message")) {
			draw_text("Back");
		}
	} else {
		draw_text("Quit");
	}
}

void display_interface(Interface * interface) {
	Menu * current_menu = interface->current_menu();
	if(current_menu != NULL) {
		current_menu->display();
	}
	display_inline_menu(interface);
}

void draw_and_highlight_text(const std::string & text, bool highlight) {
	if(highlight) {
		glPushAttrib(GL_CURRENT_BIT);
			glColor3ub(230, 230, 230);
			draw_text(text);
			options::selection_color.use();
			glPushMatrix();
				glTranslatef(1, 1, 0);
				draw_text(text);
			glPopMatrix();
		glPopAttrib();
	} else {
		draw_text(text);
	}
}

void display_menu_item(MenuItem * item) {
	glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
			options::clear_color.use();
			glRectf(0.0, 0.0, (font.width + 1 ) * item->name.length(), font.height);
		glPopAttrib();
	glPopMatrix();
	draw_and_highlight_text(item->name, item->is_current());
}

template<typename OptionType>
void display_boolean_option(MenuItem * menu_item, OptionType option, OptionType value, bool can_enter = false) {
	std::string title = menu_item->name;
	if(menu_item->is_current() && can_enter) {
		title.resize(value_shift - 7, ' ');
		title += "<start>";
	} else {
		title.resize(value_shift, ' ');
	}
	if(option & value) {
		title += "[   ][ON]";
	} else {
		title += "[OFF][  ]";
	}
	draw_and_highlight_text(title, menu_item->is_current());
}

void display_screensaver_option(MenuItem * menu_item) {
	display_boolean_option(
		menu_item,
		options::screensaver_kind, menu_item->options.screensaver_kind,
		true
	);
}

void toggle_screensaver_option(unsigned char key, int special_key, MenuItem * item) {
	SCREENSAVER_KIND screensaver_kind = item->options.screensaver_kind;
	if(key == ENTER_KEY) {
		screensaver.kind = screensaver_kind;
		application.set(SCREENSAVER_MODE);
	} else if(special_key == GLUT_KEY_LEFT) {
		options::screensaver_kind = SCREENSAVER_KIND (
			options::screensaver_kind & ~screensaver_kind
		);
		options::save_config();
	} else if(special_key == GLUT_KEY_RIGHT) {
		options::screensaver_kind = SCREENSAVER_KIND (
			options::screensaver_kind | screensaver_kind
		);
		options::save_config();
	}
	//std::cout << screensaver_kind << " " << options::screensaver_kind << std::endl;
}

void display_menu(Menu * menu) {
	draw_text(menu->name, 0, screen.height - font.height);
	glPushMatrix();
		glTranslatef(0, - font.height * 4, 0);
		int line = 0;
		int column = 0;

		int current_item_vp = 0;
		int current_item_hp = 0;

		for(MenuItems::iterator item =
			menu->items.begin();
			item != menu->items.end();
			item++, line++
		) {
			column = line / 8;
			int vertical_position = screen.height - font.height * 2 * ( line - column * 8 );
			int horizontal_position = column * 8 * ( font.width + 1 );
			if(item->is_current()) {
				current_item_hp = horizontal_position;
				current_item_vp = vertical_position;
			} else {
				glPushMatrix();
					glTranslatef(horizontal_position, vertical_position, 0);
					item->display();
				glPopMatrix();
			}
		}
		if(menu->current_item() != NULL) {
			glPushMatrix();
				glTranslatef(current_item_hp, current_item_vp, 0);
				menu->current_item()->display();
			glPopMatrix();
		}

	glPopMatrix();
}

void display_message(Menu * menu) {
	glPushMatrix();
		glTranslatef(0, screen.height - font.height, 0);
		draw_text(menu->name);
		glTranslatef(0, - font.height * 3, 0);
		draw_text("No levels found");
		if(menu->current_item() != NULL) {
			glTranslatef(0, - font.height * 3, 0);
			menu->current_item()->display();
		}
	glPopMatrix();
}

void handle_interface(unsigned char key, int special_key, Interface * interface) {
	if(key == ESCAPE_KEY) {
		if(interface->menus_stack.size() > 1) {
			interface->previous_menu();
		} else {
			application.quit();
		}
	}
	if(interface->current_menu() != NULL) {
		interface->current_menu()->handle(key, special_key);
	}
}

void handle_options_menu(unsigned char key, int special_key, Menu * menu) {
	if(special_key == GLUT_KEY_DOWN) {
		menu->next_item();
	} else if(special_key == GLUT_KEY_UP) {
		menu->previous_item();
	} else {
		if(menu->current_item() != NULL) {
			menu->current_item()->handle(key, special_key);
		}
	}
}

void handle_menu(unsigned char key, int special_key, Menu * menu) {
	if(special_key == GLUT_KEY_DOWN) {
		menu->next_item();
	} else if(special_key == GLUT_KEY_UP) {
		menu->previous_item();
	} else if(special_key == GLUT_KEY_RIGHT) {
		if(menu->items.size() > 8) {
			int last_column_size = menu->items.size() % 8;
			int last_steps = 0;
			int additional_steps = 0;
			for(int i = 0; i < 8; i++) {
				menu->_current_item++;
				if(menu->_current_item == menu->items.end()) {
					last_steps = i;
					std::cout << last_steps << std::endl;
					menu->_current_item++;
					if(last_steps < last_column_size) {
						additional_steps = last_column_size - last_steps;
					} else {
						additional_steps = last_column_size - last_steps + 8;
					}
					for(int i = 0; i < additional_steps - 1; i++) {
						menu->_current_item++;
					}
					break;
				}
			}
		}
	} else if(special_key == GLUT_KEY_LEFT) {
		if(menu->items.size() > 8) {
			int last_column_size = menu->items.size() % 8;
			int last_steps = 0;
			int additional_steps = 0;
			for(int i = 0; i < 8; i++) {
				menu->_current_item--;
				if(menu->_current_item == menu->items.end()) {
					last_steps = i;
					std::cout << last_steps << std::endl;
					menu->_current_item--;
					if(last_steps < last_column_size) {
						additional_steps = last_column_size - last_steps;
					} else {
						additional_steps = last_column_size - last_steps + 8;
					}
					for(int i = 0; i < additional_steps - 1; i++) {
						menu->_current_item--;
					}
					break;
				}
			}
		}
	} else if(special_key == GLUT_KEY_END) {
		//menu->go_to_last = _current_item = --menu->items.end();
	} else if(special_key == GLUT_KEY_HOME) {
		//menu->_current_item = menu->items.begin();
	} else {
		if(menu->current_item() != NULL) {
			menu->current_item()->handle(key, special_key);
		}
	}
}

void next_menu(unsigned char key, int special_key, MenuItem * menu_item) {
	if(key == ENTER_KEY) {
		menu_item->menu->interface->next_menu(menu_item->next_menu);
	}
}

void previous_menu(unsigned char key, int special_key, MenuItem * menu_item) {
	if(key == ENTER_KEY) {
		menu_item->menu->interface->previous_menu();
	}
}

void quit(unsigned char key, int special_key, MenuItem * menu_item) {
	if(key == ENTER_KEY) {
		application.quit();
	}
}

bool filter_yaml(dirent * entry) {
	return file::has_extension(entry->d_name, "yaml");
}

void start_game(unsigned char key, int special_key, MenuItem * menu_item) {
	if(key == ENTER_KEY) {
		game.kind = menu_item->options.game_kind;
		//game.load(menu_item.level);
		application.set(GAMEPLAY_MODE);
	}
}

void select_level(unsigned char key, int special_key, MenuItem * menu_item) {
	if(key == ENTER_KEY) {
		menu_item->next_menu->items.clear();
		std::list< std::string > levels;
		std::string path = options::levels_directory + menu_item->name;
		bool levels_are_found = false;
		if(directory::read(path, DT_REG, levels, filter_yaml)) {
			levels.sort();
			if(!levels.empty()) {
				//menu_item->title >> game.kind;
				for( std::list< std::string >::iterator
					level = levels.begin();
					level != levels.end();
					level++
				) {
					menu_item->next_menu->add_item(*level, display_menu_item, start_game);
				}
				//GAME_KIND _game_kind = NO_GAME;
				//_menu_item->title >> _game_kind;
				levels_are_found = true;
				menu_item->menu->interface->next_menu(menu_item->next_menu);
			}
		}
		if(!levels_are_found) {
			Menu * message = menu_item->menu->interface->find_menu("Message");
			menu_item->menu->interface->next_menu(message);
		}
		//interface->menus["Games"].add_item(lib::to_string(game_kind), GAMEPLAY_MODE);
		//application.set(GAMEPLAY_MODE);
	}
}

void clear_rectancle_for_menu_item(int length) {
	glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
			options::clear_color.use();
			glRectf(options::padding, options::padding, (font.width + 1 ) * length, font.height);
		glPopAttrib();
	glPopMatrix();
}

void display_padding_option(MenuItem * menu_item) {
	clear_rectancle_for_menu_item(menu_item->name.length());
	std::string title = menu_item->name;
	if(options::padding < 0)
		title.resize(value_shift - 1, ' ');
	else
		title.resize(value_shift, ' ');
	draw_and_highlight_text(title + to_string(options::padding), menu_item->is_current());
}

void handle_padding_option(unsigned char key, int special_key, MenuItem * menu_item) {
	if(special_key == GLUT_KEY_LEFT) {
		if(options::padding > -5) {
			options::padding -= 1;
			default_shape.load(options::shape_options);
			font.load(options::fonts_directory, options::font_name);
			options::save_config();
		}
	} else if(special_key == GLUT_KEY_RIGHT) {
		if(options::padding < 5) {
			options::padding += 1;
			default_shape.load(options::shape_options);
			font.load(options::fonts_directory, options::font_name);
			options::save_config();
		}
	}
	std::cout << options::padding << std::endl;
}

void load_interface(Interface * interface) {
	std::cout << "Interface: " << std::ends;

	Menus::iterator menu_iterator;
	MenuItems::iterator item_iterator;

	Menu * menu = NULL;

	interface->add_menu("Main menu", display_menu, handle_menu);
		interface->add_menu("Games", display_menu, handle_menu);
			interface->add_menu("Levels", display_menu, handle_menu);
		//interface->add_menu("Options", display_options_menu, handle_menu);
		interface->add_menu("Options", display_menu, handle_options_menu);
			interface->add_menu("Screensavers", display_menu, handle_options_menu);
		interface->add_menu("Extras", display_menu, handle_menu);
			interface->add_menu("Images", display_menu, handle_menu);
	interface->add_menu("Message", display_message, handle_menu);
	interface->add_menu("Previous menu", display_menu, handle_menu);

	menu = interface->find_menu("Main menu");
	menu->add_item("Games", display_menu_item, next_menu, interface->find_menu("Games"));
	menu->add_item("Options", display_menu_item, next_menu, interface->find_menu("Options"));
	menu->add_item("Extras", display_menu_item, next_menu, interface->find_menu("Extras"));

	menu = interface->find_menu("Games");
	for(GAME_KIND game_kind = SNAKE; game_kind <= CORNERS; game_kind++) {
		menu->add_item(to_string(game_kind), display_menu_item, select_level, interface->find_menu("Levels"));
	}

	menu = interface->find_menu("Options");
	menu->add_item("Padding", display_padding_option, handle_padding_option);

	menu = interface->find_menu("Extras");
	menu->add_item("Screensavers", display_menu_item, next_menu, interface->find_menu("Screensavers"));
	menu->add_item("Images", display_menu_item, next_menu, interface->find_menu("Images"));

	menu = interface->find_menu("Screensavers");
	for ( SCREENSAVER_KIND
		screensaver_kind = LIFE_SCREENSAVER;
		screensaver_kind <= TIMER_SCREENSAVER;
		screensaver_kind++
	) {
		MenuItem * item = menu->add_item(
			to_string(screensaver_kind),
			display_screensaver_option, toggle_screensaver_option
		);
		item->options.screensaver_kind = screensaver_kind;
		//item_handler = start_screensaver;
	}

	menu = interface->find_menu("Previous menu");
	menu->add_item("Back", display_menu_item, previous_menu);

	menu = interface->find_menu("Message");
	menu->add_item("Ok", display_menu_item, previous_menu);

	std::cout << "ok" << std::endl;

	interface->displayer = display_interface;
	interface->handler = handle_interface;

}

/*
void quick_start(unsigned char key, int special_key, MenuItem * _menu_item) {
	if(key == ENTER_KEY) {
		game.kind = SOKOBAN;
		game.load("levels/Sokoban/Level-1.yaml");
		application.set(GAMEPLAY_MODE);
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
