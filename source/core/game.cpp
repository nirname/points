#include "game.hpp"

#include "point.hpp"
#include "emitter.hpp"
#include "library.hpp"

#include "drawing.hpp"

#include "convert.hpp"
#include "emitter.hpp"
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

void Game::handle(unsigned char key, int special_key) {}

void Game::print() {
	std::cout << "Game:" << std::endl;
	std::cout << "  colors:\n" << colors;
	std::cout << "  shapes:\n" << shapes;
	std::cout << "  fields:\n" << fields;
	std::cout << "  views:\n" << views;
	std::cout << "  object kinds:\n" << object_kinds;
	std::cout << "  objects:\n" << objects;
	std::cout << std::endl;
}

void Game::display() {
	//draw_text(to_string(kind));
	/*for(graphics::AnimationMapping::Iterator i = animations.begin(); i != animations.end(); ++i) {
		i->second->next();
	}*/
	//graphics::write(lib::to_string(kind));
	//glPushMatrix();
	for(ViewManager::Iterator view = views.begin(); view != views.end(); ++view) {
		view->second->display();
	}
	//glPopMatrix();
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
	return load_yaml_option(colors, level, "colors");
}

int Game::load_shapes(const YAML::Node & level) {
	return load_yaml_option(shapes, level, "shapes");
}

int Game::load_object_kinds(const YAML::Node & level) {
	YAML::Node node = level["kinds"];
	if(node) {
		std::string key;
		YAML::Node value;
		for(YAML::const_iterator iterator = node.begin(); iterator != node.end(); ++iterator) {
			try {
				key = iterator->first.as<std::string>();
				value = iterator->second;
			} catch(YAML::TypedBadConversion<std::string()> & exception) {
				continue;
			}
			ObjectKind * object_kind = object_kinds.add(key);
			if(object_kind != NULL) {
				if(value["color"] && value["color"].IsScalar()) {
					try {
						object_kind->color = colors[value["color"].as<std::string>()];
					} catch(YAML::TypedBadConversion<std::string()> & exception) {}
				}
			}
		}
	} else {
		return 1;
	}
	return 0;
}

int Game::load_objects(const YAML::Node & level) {
	return 0;
}

int Game::load_fields(const YAML::Node & level) {
	YAML::Node node = level["fields"];
	if(node) {
		std::string key;
		YAML::Node value;
		for(YAML::const_iterator iterator = node.begin(); iterator != node.end(); ++iterator) {
			try {
				key = iterator->first.as<std::string>();
				value = iterator->second;
			} catch(YAML::TypedBadConversion<std::string()> & exception) {
				continue;
			}
			Field * field = fields.add(key);
			if(field != NULL) {
				try {
					if(value["size"]) {
						field->size = value["size"].as<Size>();
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
			} catch(YAML::TypedBadConversion<std::string()> & exception) {
				continue;
			}
			View * view = views.add(key);
			if(view != NULL) {
				if(value["size"]) {
					try {
						view->size = value["size"].as<Size>();
					} catch(YAML::TypedBadConversion<Size> & exception) {}
				}
				if(value["field"] && value["field"].IsScalar()) {
					try {
						view->field = fields[value["field"].as<std::string>()];
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
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
			}
		}
	} else {
		return 1;
	}
	return 0;
}

int Game::load_level(const YAML::Node & level) {
	int result = 0;

	result |= load_game_options(level);
	result |= load_colors(level);
	result |= load_shapes(level);
	result |= load_fields(level);
	result |= load_views(level);
	result |= load_object_kinds(level);
	result |= load_objects(level);

	return result;
}

// Loads all properties
//
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

	//std::cout << "GAME STATUS: " << loaded << std::endl;
	return loaded;

} // load()
