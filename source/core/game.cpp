#include "game.hpp"

#include "point.hpp"
#include "emitters.hpp"
#include "library.hpp"

#include "drawing.hpp"

#include "convert.hpp"
#include "yaml_adapter.hpp"
#include "functionals.hpp"

Game::Game(): kind(NO_GAME), paused(false), loaded(false) {
	screen_size.width = 10;
	screen_size.height = 10;
}

Game::~Game() {
	unload();
}

int Game::width() {
	return screen_size.width;
}

int Game::height() {
	return screen_size.height;
}

void Game::pause() {
	paused = true;
}

void Game::resume() {
	paused = false;
}

void Game::handle(unsigned char key, int special_key) {

	/*for(Controls::iterator i = controls.begin(); i != controls.end(); ++i) {
		std::cout << "    " << i->first << ": " << i->second << std::endl;
	}*/

	if(!paused) {
		Field * field = fields["field"];
		Object * sokoban = objects["sokoban"];
		Point step;
		switch(key) {
			case GLUT_KEY_UP:    step = Point( 0,  1); break;
			case GLUT_KEY_DOWN:  step = Point( 0, -1); break;
			case GLUT_KEY_LEFT:  step = Point(-1,  0); break;
			case GLUT_KEY_RIGHT: step = Point( 1,  0); break;
		}
		//animations["Scale"]->do_after = move_sokoban;
		//animations["Scale"]->start();
		//, animations[std::string("Scale")]
		//sokoban->move(field, step);
		//sokoban->move(field, step);
		//std::cout << "Key: " << key << std::endl;
		//glutPostRedisplay();
		//printf("%i", key);
		//std::cout << std::endl;
	}

	/*if(key = GLUT_KEY_UP) {
		for(FieldManager::Iterator i = fields.begin(); i != fields.end(); ++i) {
		}
	}*/

}

void Game::print() {
	std::cout << "Game:" << std::endl;
	std::cout << "  colors:\n" << colors;
	std::cout << "  shapes:\n" << shapes;
	std::cout << "  fields:\n" << fields;
	std::cout << "  views:\n" << views;
	std::cout << "  object kinds:\n" << object_kinds;
	std::cout << "  objects:\n" << objects;
	std::cout << "  controls:\n";
	for(Controls::iterator i = controls.begin(); i != controls.end(); ++i) {
		std::cout << "    " << i->first << ": " << i->second << std::endl;
	}
	std::cout << std::endl;
}

/*template<typename T>
void print(T * instance) {
	std::cout << instance << std::endl;
}*/

void Game::display() {
	/*for(graphics::AnimationMapping::Iterator i = animations.begin(); i != animations.end(); ++i) {
		i->second->next();
	}*/
	views.each(View::display);
}

bool Game::unload() {
	std::cout << "Game unloading: " << std::ends;

	loaded = false;
	paused = false;

	colors.clear();
	shapes.clear();

	fields.clear();
	views.clear();
	object_kinds.clear();
	objects.clear();

	std::cout << "done" << std::endl;
	return true;
}

int Game::load_game_options(const YAML::Node & level) {
	if(level["game"]) {
		const YAML::Node & game_options = level["game"];
		if(game_options.IsMap() && game_options["screen"]) {
			return load_yaml_option(screen_size, game_options, "screen");
		}
	}
	return 0;
}

int Game::load_colors(const YAML::Node & level) {
	colors.insert("black", new Color(pallete::black));
	colors.insert("dark-gray", new Color(pallete::dark_gray));
	colors.insert("gray", new Color(pallete::gray));
	colors.insert("light-gray", new Color(pallete::light_gray));
	colors.insert("white", new Color(pallete::white));
	colors.insert("red", new Color(pallete::red));
	colors.insert("red-orange", new Color(pallete::red_orange));
	colors.insert("orange", new Color(pallete::orange));
	colors.insert("yellow-orange", new Color(pallete::yellow_orange));
	colors.insert("yellow", new Color(pallete::yellow));
	colors.insert("yellow-green", new Color(pallete::yellow_green));
	colors.insert("green", new Color(pallete::green));
	colors.insert("sea-green", new Color(pallete::sea_green));
	colors.insert("blue-green", new Color(pallete::blue_green));
	colors.insert("cyan", new Color(pallete::cyan));
	colors.insert("sky-blue", new Color(pallete::sky_blue));
	colors.insert("soft-blue", new Color(pallete::soft_blue));
	colors.insert("blue", new Color(pallete::blue));
	colors.insert("purple", new Color(pallete::purple));
	colors.insert("violet", new Color(pallete::violet));
	colors.insert("red_violet", new Color(pallete::red_violet));

	load_yaml_option(colors, level, "colors");

	return 0;
}

int Game::load_shapes(const YAML::Node & level) {
	return load_yaml_option(shapes, level, "shapes");
}

int Game::load_object_kinds(const YAML::Node & level) {
	const YAML::Node & node = level["kinds"];
	if(node) {
		std::string key;
		YAML::Node value;
		for(YAML::const_iterator iterator = node.begin(); iterator != node.end(); ++iterator) {
			try {
				key = iterator->first.as<std::string>();
				value = iterator->second;
			} catch(YAML::TypedBadConversion<std::string> & exception) {
				continue;
			}
			ObjectKind * object_kind = object_kinds.add(key);
			if(object_kind != NULL) {
				if(value["color"] && value["color"].IsScalar()) {
					try {
						object_kind->color = colors[value["color"].as<std::string>()];
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
			}
		}
	} else {
		return 1;
	}
	return 0;
}

int Game::load_objects(const YAML::Node & object_kinds_node, Field * field) {
	std::cout << "loading objects" << std::endl;
	//const YAML::Node & object_kinds_node = level["objects"];
	if(object_kinds_node && object_kinds_node.IsMap()) {
		for(YAML::const_iterator k = object_kinds_node.begin(); k != object_kinds_node.end(); ++k) {

			ObjectKind * object_kind = NULL;
			try {
				object_kind = object_kinds[k->first.as<std::string>()];
			} catch(YAML::TypedBadConversion<std::string> & exception) {
			}

			if(object_kind != NULL) {
				const YAML::Node & objects_node = k->second;
				if(objects_node.IsSequence()) {
					for(YAML::const_iterator o = objects_node.begin(); o != objects_node.end(); ++o) {

						const YAML::Node & object_node = *o;

						Object * object = NULL;
						Point position(0, 0);

						if(object_node.IsSequence()) {
							if(object_node.size() == 2) {
								object = objects.add();
								position.column = object_node[0].as<int>();
								position.row = object_node[1].as<int>();
							} else if(object_node.size() == 3) {
								try {
									object = objects.add(object_node[0].as<std::string>());
								} catch(YAML::TypedBadConversion<std::string> & exception) {}
								position.column = object_node[1].as<int>();
								position.row = object_node[2].as<int>();
							}
						} else if(object_node.IsMap()) {
						}

						if(object != NULL) {
							object->kind = object_kind;
							if(field != NULL) {
								field->data.add(object, position);
							}
						}

					}
				}
			}

		}
	}
	return 0;
}

int Game::load_fields(const YAML::Node & level) {
	const YAML::Node & node = level["fields"];
	if(node) {
		std::string key;
		for(YAML::const_iterator iterator = node.begin(); iterator != node.end(); ++iterator) {
			try {
				key = iterator->first.as<std::string>();
			} catch(YAML::TypedBadConversion<std::string> & exception) {
				continue;
			}
			Field * field = fields.add(key);
			if(field != NULL) {
				const YAML::Node & value = iterator->second;
				try {
					if(value["size"]) {
						field->size = value["size"].as<Size>();
					}
					if(value["objects"]) { // unnecessary
						load_objects(value["objects"], field);
						//field->
					}
				} catch(YAML::TypedBadConversion<Size> & exception) {}
			}
		}
	} else {
		return 1;
	}
	return 0;
}

int Game::load_views(const YAML::Node & level) {
	YAML::Node node = level["views"];
	if(node) {
		std::string key;
		YAML::Node value;
		for(YAML::const_iterator iterator = node.begin(); iterator != node.end(); ++iterator) {
			try {
				key = iterator->first.as<std::string>();
				value = iterator->second;
			} catch(YAML::TypedBadConversion<std::string> & exception) {
				continue;
			}
			// TODO: move this to convert
			View * view = views.add(key);
			if(view != NULL) {
				if(value["field"] && value["field"].IsScalar()) {
					try {
						view->field = fields[value["field"].as<std::string>()];
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
				if(value["size"]) {
					try {
						view->size = value["size"].as<Size>();
					} catch(YAML::TypedBadConversion<Size> & exception) {}
				} else {
					view->adjust_size();
				}
				if(value["background_color"] && value["background_color"].IsScalar()) {
					try {
						view->background_color = colors[value["background_color"].as<std::string>()];
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
				if(value["field_color"] && value["field_color"].IsScalar()) {
					try {
						view->field_color = colors[value["field_color"].as<std::string>()];
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
				if(value["cells_color"] && value["cells_color"].IsScalar()) {
					try {
						view->cells_color = colors[value["cells_color"].as<std::string>()];
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
				if(value["grid_color"] && value["grid_color"].IsScalar()) {
					try {
						view->grid_color = colors[value["grid_color"].as<std::string>()];
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
				if(value["border_color"] && value["border_color"].IsScalar()) {
					try {
						view->border_color = colors[value["border_color"].as<std::string>()];
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
				if(value["position"]) {
					try {
						view->position = value["position"].as<Point>();
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
				if(value["offset"]) {
					try {
						view->offset = value["offset"].as<Point>();
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
				if(value["direction"]) {
					try {
						view->direction = value["direction"].as<Point>();
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
			}
		}
	} else {
		return 1;
	}
	return 0;
}

int Game::load_controls(const YAML::Node & level) {
	YAML::Node node = level["controls"];
	if(node && node.IsMap()) {
		std::string player;
		std::string object_name;
		for(YAML::const_iterator iterator = node.begin(); iterator != node.end(); ++iterator) {
			try {
				player = iterator->first.as<std::string>();
				object_name = iterator->second.as<std::string>();
				Object * object = objects[object_name];
				if(object != NULL) {
					controls[player] = object;
				}
			} catch(YAML::TypedBadConversion<std::string> & exception) {}
		}
	}
	return 0;
}

/// Loads level
//
/// level should be a hash
///
int Game::load_level(const YAML::Node & level) {
	int result = 0;

	result |= load_game_options(level);
	result |= load_colors(level);
	result |= load_shapes(level);
	result |= load_object_kinds(level);
	result |= load_fields(level);
	result |= load_views(level);
	result |= load_objects(level);
	result |= load_controls(level);

	return result;
}

/// Loads all properties
//
/// Properties are load from YAML
/// Logic depends on game kind
///
bool Game::load(GAME_KIND game_kind, const std::string & level_path) {

	std::cout << "Loading game:" << std::endl;

	if(loaded) {
		unload();
	}

	if(load_yaml_file(level_path, bind<const YAML::Node &>(this, &Game::load_level)) == 0) {
		loaded = true;
		std::cout << "done" << std::endl;
		print();
	} else {
		unload();
		loaded = false;
		std::cout << "failed" << std::endl;
	}

	return loaded;

}
