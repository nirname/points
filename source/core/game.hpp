#pragma once

#include "game_kind.hpp"

#include "yaml-cpp/yaml.h"

#include "size.hpp"

#include <string>
#include "manager.hpp"

#include "color.hpp"
#include "shape.hpp"
#include "object_kind.hpp"

typedef Manager<std::string, Color> ColorManager;
typedef Manager<std::string, Shape> ShapeManager;
typedef Manager<std::string, ObjectKind> ObjectKindManager;

#include "screensaver_kind.hpp"

/// Describes current game
//
struct Game {

	GAME_KIND kind;
	bool paused;
	bool loaded;

	//bool no_levels;

	ColorManager colors;
	ShapeManager shapes;
	ObjectKindManager object_kinds;

	/*FieldMapping      fields;
	ViewMapping       views;
	ObjectKindMapping object_kinds;
	ObjectMapping     objects;*/
	//Entities          entities; // TODO: Unnamed objects
	//ControlsMapping   controls;

	//graphics::AnimationMapping animations;
	//LevelList levels;

	//InteractionMap interactions;

	//LevelListIterator current_level;
	//LevelMapping levels;

	Size screen_size;

	Game();

	int load_attributes(const YAML::Node & level);

	template<typename Type>
	int load_attribute(Type & attribute, const YAML::Node & level, const char * key);

	int load_defaults();
	//void load_interactions(const YAML::Node &);
	void load_objects(const YAML::Node & level);
	void load_default_colors();
	void load_default_shapes();

	void load_game_options(const YAML::Node &);

	bool load(GAME_KIND game_kind, const std::string & level_path);
	bool unload();

	void pause();
	void resume();

	void handle(unsigned char key, int special_key);

	void print();

	void display();

	int width();
	int height();

};
