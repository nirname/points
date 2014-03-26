#pragma once

// Describes current game
//
struct Game {

	GAME_KIND kind;
	bool paused;
	bool loaded;

	FieldMapping      fields;
	ViewMapping       views;
	ColorMapping      colors;
	ShapeMapping      shapes;
	ObjectKindMapping object_kinds;
	ObjectMapping     objects;
	//Entities          entities; // TODO: Unnamed objects
	ControlsMapping   controls;
	graphics::AnimationMapping animations;
	LevelList levels;

	InteractionMap interactions;

	LevelListIterator current_level;
	//LevelMapping levels;

	Game():
		kind(NO_GAME), paused(false), loaded(false)
	{}

	template<typename Type> void load_attribute(Type & attribute, const YAML::Node & level, const char * key);

	void load_interactions(const YAML::Node &);
	void load_objects(const YAML::Node &);
	void load_default_colors();
	void load_default_shapes();

	bool load(LevelPointer);
	bool unload();

	void pause();
	void resume();

	void process(unsigned char key, int special_key);

	void print();

	void display();

};
