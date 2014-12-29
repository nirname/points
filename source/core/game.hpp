#pragma once

#include "yaml.hpp"
#include <string>

#include "game_kind.hpp"
#include "size.hpp"

#include "manager.hpp"
#include "color.hpp"
#include "shape.hpp"
#include "object_kind.hpp"
#include "object.hpp"
#include "field.hpp"
#include "view.hpp"

typedef Manager<std::string, Color> ColorManager;
typedef Manager<std::string, Shape> ShapeManager;
typedef Manager<std::string, ObjectKind> ObjectKindManager;
typedef Manager<std::string, Object> ObjectManager;
typedef Manager<std::string, Field> FieldManager;
typedef Manager<std::string, View> ViewManager;

/// Describes current game
//
struct Game {

	GAME_KIND kind;
	bool paused;
	bool loaded;

	//bool no_levels;

	ColorManager colors;
	ShapeManager shapes;

	FieldManager      fields;
	ViewManager       views;
	ObjectKindManager object_kinds;
	ObjectManager     objects;
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
