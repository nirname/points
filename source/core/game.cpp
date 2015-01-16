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
	std::cout << "  colors: " << colors << std::endl;
	std::cout << "  shapes: " << shapes << std::endl;
	std::cout << "  fields: " << fields << std::endl;
	std::cout << "  views: " << views << std::endl;
	std::cout << "  object kinds: " << object_kinds << std::endl;
	std::cout << "  objects: " << objects << std::endl;
}

void Game::display() {

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
		for(YAML::const_iterator iterator = node.begin(); iterator != node.end(); ++iterator) {
			try {
				key = iterator->first.as<std::string>();
			} catch(YAML::TypedBadConversion<std::string()> & exception) {
				continue;
			}
			ObjectKind * object_kind = object_kinds.add(key);
			if(object_kind != NULL) {
				if(node["color"] && node["color"].IsScalar()) {
					try {
						object_kind->color = colors[node["color"].as<std::string>()];
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
		for(YAML::const_iterator iterator = node.begin(); iterator != node.end(); ++iterator) {
			try {
				key = iterator->first.as<std::string>();
			} catch(YAML::TypedBadConversion<std::string()> & exception) {
				continue;
			}
			Field * field = fields.add(key);
			if(field != NULL) {
				try {
					if(node["size"]) {
						field->size = node["size"].as<Size>();
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
		for(YAML::const_iterator iterator = node.begin(); iterator != node.end(); ++iterator) {
			try {
				key = iterator->first.as<std::string>();
			} catch(YAML::TypedBadConversion<std::string()> & exception) {
				continue;
			}
			View * view = views.add(key);
			if(view != NULL) {
				if(node["size"]) {
					try {
						view->size = node["size"].as<Size>();
					} catch(YAML::TypedBadConversion<Size> & exception) {}
				}
				if(node["background_color"] && node["background_color"].IsScalar()) {
					try {
						view->background_color = colors[node["background_color"].as<std::string>()];
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
				if(node["field_color"] && node["field_color"].IsScalar()) {
					try {
						view->field_color = colors[node["field_color"].as<std::string>()];
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
				if(node["cells_color"] && node["cells_color"].IsScalar()) {
					try {
						view->cells_color = colors[node["cells_color"].as<std::string>()];
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
				if(node["grid_color"] && node["grid_color"].IsScalar()) {
					try {
						view->grid_color = colors[node["grid_color"].as<std::string>()];
					} catch(YAML::TypedBadConversion<std::string> & exception) {}
				}
				if(node["border_color"] && node["border_color"].IsScalar()) {
					try {
						view->border_color = colors[node["border_color"].as<std::string>()];
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
