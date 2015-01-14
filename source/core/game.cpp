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
	//std::cout << "  shapes: " << shapes << std::endl;
	//std::cout << "  fields: " << fields << std::endl;
	//std::cout << "  views: " << views << std::endl;
	//std::cout << "  object kinds: " << object_kinds << std::endl;
	//std::cout << "  objects: " << objects << std::endl;
}

void Game::display() {}

bool Game::unload() {
	std::cout << "Game unloading: " << std::ends;

	loaded = false;
	paused = false;

	colors.clear();
	//shapes.clear();

	//fields.clear();
	//views.clear();
	//object_kinds.clear();
	//objects.clear();

	std::cout << "done" << std::endl;
	return true;
}

int Game::load_level(const YAML::Node & level) {
	int result = 0;

	//result |= load_game_options(level);

	result |= load_yaml_option(colors, level, "colors");
	//result |= load_yaml_option(shapes, level, "shapes");

	//result |= load_yaml_option(fields, level, "fields");
	//result |= load_yaml_option(views, level, "views");
	//result |= load_yaml_option(object_kinds, level, "object_kinds");
	//result |= load_yaml_option(objects, level, "objects");

	//return result;
	return 1;
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

	std::cout << "GAME STATUS: " << loaded << std::endl;
	return loaded;

} // load()
