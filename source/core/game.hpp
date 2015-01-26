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

typedef Manager<std::string, Field> FieldManager;
typedef Manager<std::string, View> ViewManager;
typedef Manager<std::string, ObjectKind> ObjectKindManager;
typedef Manager<std::string, Object> ObjectManager;

/// Describes current game
//
struct Game {

	GAME_KIND kind;
	bool paused;
	bool loaded;

	ColorManager colors;
	ShapeManager shapes;

	FieldManager      fields;
	ViewManager       views;
	ObjectKindManager object_kinds;
	ObjectManager     objects;

	Size screen_size;

	Game();
	~Game();

	int load_game_options(const YAML::Node & level);
	int load_colors(const YAML::Node & level);
	int load_shapes(const YAML::Node & level);
	int load_object_kinds(const YAML::Node & level);
	int load_objects(const YAML::Node & object_kinds_node, Field * field = NULL);
	//int load_objects(const YAML::Node & level);
	int load_fields(const YAML::Node & level);
	int load_views(const YAML::Node & level);

	int load_level(const YAML::Node & level);

	bool load(GAME_KIND game_kind, const std::string & level_path);
	bool unload();

	void pause();
	void resume();

	void handle(unsigned char key, int special_key);

	void display();

	void print();

	int width();
	int height();

};
