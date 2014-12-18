#include "user_interface.hpp"

#include <iostream>

#include "color.hpp"
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
			Color(LIGHT_GRAY).use();
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

// TODO: refactor this one
void display_multicolumn_menu(Menu * menu) {
	glPushMatrix();
		glTranslatef(0, screen.height - font.height, 0);
		draw_text(menu->name);
	glPopMatrix();
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
			int horizontal_position = column * 10 * ( font.width + 1 );
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

void display_menu(Menu * menu) {
	glPushMatrix();
		glTranslatef(0, screen.height - font.height, 0);
		draw_text(menu->name);
		glTranslatef(0, - font.height * 3, 0);
		int line = 0;
		for(MenuItems::iterator item =
			menu->items.begin();
			item != menu->items.end();
			item++, line++
		) {
			glPushMatrix();
				glTranslatef(0, - font.height * 2 * line, 0);
				item->display();
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

void handle_menu(unsigned char key, int special_key, Menu * menu) {
	if(special_key == GLUT_KEY_DOWN) {
		menu->next_item();
	} else if(special_key == GLUT_KEY_UP) {
		menu->previous_item();
	} else if(special_key == GLUT_KEY_END) {
		menu->go_to_last();
	} else if(special_key == GLUT_KEY_HOME) {
		menu->go_to_first();
	} else {
		if(menu->current_item() != NULL) {
			menu->current_item()->handle(key, special_key);
		}
	}
}

void handle_multicolumn_menu(unsigned char key, int special_key, Menu * menu) {
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
		menu->go_to_last();
	} else if(special_key == GLUT_KEY_HOME) {
		menu->go_to_first();
	} else {
		if(menu->current_item() != NULL) {
			menu->current_item()->handle(key, special_key);
		}
	}
}

void handle_menu_item(unsigned char key, int special_key, MenuItem * menu_item) {
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
		game.load(menu_item->options.game_kind, menu_item->options.level);
		application.set(GAMEPLAY_MODE);
	}
}

void select_level(unsigned char key, int special_key, MenuItem * menu_item) {
	if(key == ENTER_KEY) {
		menu_item->next_menu->items.clear();
		std::list< std::string > levels;
		std::string path = options::levels_directory + menu_item->name;
		bool levels_are_found = false;
		MenuItem * level_item;
		if(directory::read(path, DT_REG, levels, filter_yaml)) {
			//if(levels.size() > 1) {
				levels.sort();
				if(!levels.empty()) {
					for( std::list< std::string >::iterator
						level = levels.begin();
						level != levels.end();
						level++
					) {
						level_item = menu_item->next_menu->add_item(*level, display_menu_item, start_game);
						level_item->options.game_kind = menu_item->options.game_kind;
						level_item->options.level = *level;
					}
					levels_are_found = true;
					menu_item->menu->interface->next_menu(menu_item->next_menu);
				}
			//} else {}
		}
		if(!levels_are_found) {
			Menu * message = menu_item->menu->interface->find_menu("Message");
			menu_item->menu->interface->next_menu(message);
		}
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

template<typename OptionType>
void display_option(MenuItem * menu_item, const OptionType & option) {
	clear_rectancle_for_menu_item(menu_item->name.length());
	std::string title = menu_item->name;
	title.resize(value_shift, ' ');
	draw_and_highlight_text(title + "~", menu_item->is_current());
}

template<>
void display_option<int>(MenuItem * menu_item, const int & option) {
	clear_rectancle_for_menu_item(menu_item->name.length());
	std::string title = menu_item->name;
	title.resize(value_shift - ((option < 0)? 1 : 0), ' ');
	draw_and_highlight_text(title + to_string(option), menu_item->is_current());
}

template<>
void display_option<bool>(MenuItem * menu_item, const bool & option) {
	clear_rectancle_for_menu_item(menu_item->name.length());
	std::string title = menu_item->name;
	title.resize(value_shift, ' ');
	draw_and_highlight_text(title + ((option)? "yes": "no"), menu_item->is_current());
}

template<>
void display_option<Color>(MenuItem * menu_item, const Color & option) {
	clear_rectancle_for_menu_item(menu_item->name.length());
	draw_and_highlight_text(menu_item->name, menu_item->is_current());
	glPushMatrix();
		glTranslatef(value_shift * (font.width + 1), 0, 0);
		glPushAttrib(GL_CURRENT_BIT);
			option.use();
			glRectf(0, 0, font.width * 5, font.height);
		glPopAttrib();
	glPopMatrix();
}

template<const int & option>
inline void display_option(MenuItem * menu_item) {
	display_option(menu_item, option);
}

template<const bool & option>
inline void display_option(MenuItem * menu_item) {
	display_option(menu_item, option);
}

template<const Color & option>
inline void display_option(MenuItem * menu_item) {
	display_option(menu_item, option);
}

/*void display_screensaver_option(MenuItem * menu_item) {
	display_boolean_option(
		menu_item,
		options::screensaver_kind, menu_item->options.screensaver_kind,
		true
	);
}*/

void toggle_screensaver_option(unsigned char key, int special_key, MenuItem * item) {
	SCREENSAVER_KIND screensaver_kind = item->options.screensaver_kind;
	if(key == ENTER_KEY) {
		screensaver.load(screensaver_kind);
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

/*template<SCREENSAVER_KIND option>
inline void display_option(MenuItem * menu_item) {
	display_option<bool>(menu_item, (bool)(options::screensaver_kind & option));
}*/

template<typename OptionType>
void handle_option(unsigned char key, int special_key, MenuItem * menu_item, OptionType & option) {
	throw "Undefined option handling";
}

template<>
void handle_option<int>(unsigned char key, int special_key, MenuItem * menu_item, int & option) {
	if(special_key == GLUT_KEY_LEFT) {
		option -= 1;
	} else if(special_key == GLUT_KEY_RIGHT) {
		option += 1;
	}
	options::save_config();
}

template<>
void handle_option<bool>(unsigned char key, int special_key, MenuItem * menu_item, bool & option) {
	if(special_key == GLUT_KEY_LEFT) {
		option = false;
	} else if(special_key == GLUT_KEY_RIGHT) {
		option = true;
	}
	options::save_config();
}

template<>
void handle_option<Color>(unsigned char key, int special_key, MenuItem * menu_item, Color & option) {
	if(special_key == GLUT_KEY_LEFT) {
		//option -= 1;
	} else if(special_key == GLUT_KEY_RIGHT) {
		//option += 1;
	}
	//options::save_config();
}

template<int & option>
void handle_option(unsigned char key, int special_key, MenuItem * menu_item) {
	handle_option(key, special_key, menu_item, option);
}

template<bool & option>
void handle_option(unsigned char key, int special_key, MenuItem * menu_item) {
	handle_option(key, special_key, menu_item, option);
}

template<>
void handle_option<options::padding>(unsigned char key, int special_key, MenuItem * menu_item) {
	if(
		(options::padding < 5 && special_key == GLUT_KEY_RIGHT) ||
		(options::padding > -5 && special_key == GLUT_KEY_LEFT)
	) {
		handle_option(key, special_key, menu_item, options::padding);
		default_shape.load(options::shape_options);
		font.load(options::fonts_directory, options::font_name);
	}
}

template<Color & option>
void handle_option(unsigned char key, int special_key, MenuItem * menu_item) {
	handle_option(key, special_key, menu_item, option);
}

void display_fonts(Menu * menu) {
	glPushMatrix();
		glTranslatef(0, screen.height - font.height, 0);
		draw_text(menu->name);
		glTranslatef(font.width, -font.height * 3, 0);
		glPushMatrix();
		for(int i = 33; i <= 126; i++ ) {
			draw_text(to_string((char)i));
			if((i - 33 + 1) % 15 == 0) {
				glPopMatrix();
				glTranslatef(0, -font.height * 2, 0);
				glPushMatrix();
			} else {
				glTranslatef(font.width * 2, 0, 0);
			}
		}
		glPopMatrix();
	glPopMatrix();
}

void display_color(std::string title, const Color & color) {
	glPushAttrib(GL_CURRENT_BIT);
		color.use();
		draw_text(title);
		glRectf(20 * font.width, 0, 20 * font.width + 50, font.height + 1);
	glPopAttrib();
	glTranslatef(0, - font.height - 1, 0);
}

void display_colors(Menu * menu) {
	glPushMatrix();
		glTranslatef(0, screen.height - font.height, 0);
		draw_text(menu->name);
		glTranslatef(0, -font.height * 2, 0);

		display_color("RED",           pallete::red);
		display_color("RED-ORANGE",    pallete::red_orange);
		display_color("ORANGE",        pallete::orange);
		display_color("YELLOW-ORANGE", pallete::yellow_orange);
		display_color("YELLOW",        pallete::yellow);
		display_color("YELLOW-GREEN",  pallete::yellow_green);
		display_color("GREEN",         pallete::green);
		display_color("SEA-GREEN",     pallete::sea_green);
		display_color("BLUE-GREEN",    pallete::blue_green);
		display_color("CYAN",          pallete::cyan);
		display_color("SKY-BLUE",      pallete::sky_blue);
		display_color("SOFT-BLUE",     pallete::soft_blue);
		display_color("BLUE",          pallete::blue);
		display_color("PURPLE",        pallete::purple);
		display_color("VIOLET",        pallete::violet);
		display_color("RED-VIOLET",    pallete::red_violet);

	glPopMatrix();
}

void load_interface(Interface * interface) {
	std::cout << "Interface: " << std::ends;

	Menus::iterator menu_iterator;
	MenuItems::iterator item_iterator;

	Menu * menu = NULL;
	MenuItem * menu_item = NULL;

	interface->add_menu("Main menu", display_menu, handle_menu);
		interface->add_menu("Games", display_multicolumn_menu, handle_multicolumn_menu);
			interface->add_menu("Levels", display_menu, handle_menu);
		interface->add_menu("Extras", display_menu, handle_menu);
			interface->add_menu("Screensavers", display_menu, handle_menu);
			interface->add_menu("Images", display_menu, handle_menu);
			interface->add_menu("Fonts", display_fonts, handle_menu);
			interface->add_menu("Pallete", display_colors, handle_menu);
		interface->add_menu("Options", display_menu, handle_menu);
			interface->add_menu("Video", display_menu, handle_menu);
			interface->add_menu("Interface", display_menu, handle_menu);
			interface->add_menu("Audio", display_menu, handle_menu);
	interface->add_menu("Message", display_message, handle_menu);
	interface->add_menu("Previous menu", display_menu, handle_menu);

	menu = interface->find_menu("Main menu");
	menu->add_item("Games", display_menu_item, next_menu, interface->find_menu("Games"));
	menu->add_item("Extras", display_menu_item, next_menu, interface->find_menu("Extras"));
	menu->add_item("Options", display_menu_item, next_menu, interface->find_menu("Options"));

	menu = interface->find_menu("Games");
	for(GAME_KIND game_kind = SNAKE; game_kind <= CORNERS; game_kind++) {
		menu_item = menu->add_item(to_string(game_kind), display_menu_item, select_level, interface->find_menu("Levels"));
		menu_item->options.game_kind = game_kind;
	}

	menu = interface->find_menu("Options");
	menu->add_item("Interface", display_menu_item, next_menu, interface->find_menu("Interface"));
	menu->add_item("Video", display_menu_item, next_menu, interface->find_menu("Video"));

	menu = interface->find_menu("Interface");
	menu->add_item("Padding", display_option<options::padding>, handle_option<options::padding>);
	menu->add_item("Foreword", display_option<options::foreword>, handle_option<options::foreword>);
	menu->add_item("Afterword", display_option<options::afterword>, handle_option<options::afterword>);
	menu->add_item("Selection color", display_option<options::selection_color>, handle_option<options::selection_color>);

	menu = interface->find_menu("Video");
	menu->add_item("Full screen", display_option<options::full_screen>, handle_option<options::full_screen>);
	menu->add_item("Proportional", display_option<options::proportional>, handle_option<options::proportional>);
	menu->add_item("Smooth zooming", display_option<options::smooth_zooming>, handle_option<options::smooth_zooming>);
	menu->add_item("Multisample", display_option<options::multisample>, handle_option<options::multisample>);
	menu->add_item("Game mode", display_option<options::game_mode>, handle_option<options::game_mode>);

	menu = interface->find_menu("Extras");
	menu->add_item("Screensavers", display_menu_item, next_menu, interface->find_menu("Screensavers"));
	menu->add_item("Images", display_menu_item, next_menu, interface->find_menu("Images"));
	menu->add_item("Pallete", display_menu_item, next_menu, interface->find_menu("Pallete"));
	menu->add_item("Fonts", display_menu_item, next_menu, interface->find_menu("Fonts"));

	menu = interface->find_menu("Screensavers");

	for ( SCREENSAVER_KIND
		screensaver_kind = LIFE_SCREENSAVER;
		screensaver_kind <= TIMER_SCREENSAVER;
		screensaver_kind++
	) {
		MenuItem * item = menu->add_item(to_string(screensaver_kind), display_menu_item, toggle_screensaver_option);
		item->options.screensaver_kind = screensaver_kind;
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
*/
