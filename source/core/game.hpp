#pragma once

#include "yaml-cpp/yaml.h"

enum GAME_KIND {

	NO_GAME,

	// Single player

	SNAKE,
	SOKOBAN,
	ATOMIX,
	RUSH_HOUR,
	LIGHTS,
	TETRIS,
	ROBOTS,
	LABYRINTH,
	SWAP,
	POLYMINO,
	BACKGROUND,
	LINES,
	NETWALK,
	MOWER,
	MASYU,
	RINGS,
	BOMBERMAN,
	PACMAN,
	GAME1024,

	// Multiplayer

	REVERSI,
	GOMOKU,
	FOUR_IN_A_ROW,
	TRHONE,
	BATTLESHIP,
	POINTS,
	GO,
	STICS,
	CORNERS

};

/// Describes current game
//
struct Game {

	GAME_KIND kind;
	bool paused;
	bool loaded;

	/*FieldMapping      fields;
	ViewMapping       views;
	ColorMapping      colors;
	ShapeMapping      shapes;
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

	//template<typename Type> void load_attribute(Type & attribute, const YAML::Node & level, const char * key);

	//void load_interactions(const YAML::Node &);
	void load_objects(const YAML::Node &);
	void load_default_colors();
	void load_default_shapes();

	void load_game_options(const YAML::Node &);

	bool load(std::string);
	bool unload();

	void pause();
	void resume();

	void process(unsigned char key, int special_key);

	void print();

	void display();

};
