#pragma once

template<typename Type> class Mapping;

namespace graphics {

	extern int sleep;

	void redisplay(int);
	void reshape(int, int);

	void square();
	void ngon(int, int);
	void circle();
	void star();
	void david();

	struct Color;
	struct Shape;

	typedef Color * ColorPointer;
	typedef Shape * ShapePointer;

	struct Animation;
	typedef Animation * AnimationPointer;
	typedef Mapping< Animation > AnimationMapping;
	//typedef std::map< KeyType, AnimationPointer > AnimationMap;
	//typedef AnimationMap::iterator AnimationMapIterator;
}

typedef graphics::Color Color;

namespace engine {

	struct Point;
	struct Size;
	struct Bound;

	struct Program;

	struct Screen;
	struct Level;
	struct Game;
	struct Field;
	struct View;
	struct Object;

	struct ObjectKind;
	struct ControlHandler;

	typedef Level  * LevelPointer;
	typedef Field  * FieldPointer;
	typedef View   * ViewPointer;
	typedef Object * ObjectPointer;
	typedef Point  * PointPointer;
	typedef ObjectKind * ObjectKindPointer;

	typedef Mapping< Field           >      FieldMapping;
	typedef Mapping< View            >       ViewMapping;
	typedef Mapping< ObjectKind      > ObjectKindMapping;
	typedef Mapping< Object          >     ObjectMapping;
	typedef Mapping< graphics::Color >      ColorMapping;
	typedef Mapping< graphics::Shape >      ShapeMapping;
	typedef Mapping< ControlHandler  >   ControlsMapping;

	typedef std::map< Object *, Point > ObjectInformation;
	typedef std::map< Point, Object * > PointInformation;

	typedef ObjectInformation::iterator ObjectInformationIterator;
	typedef PointInformation::iterator PointInformationIterator;

	// TODO: move it from here
	enum INTERACTION_TYPE {
		NO_INTERACTION,
		PUSH_INTERACTION,
		PULL_INTERACTION,
		JOIN_INTERACTION,
		SLAP_INTERACTION,
		DESTROY_INTERACTION,
		DIE_INTERACTION
	};

	typedef std::pair< ObjectKindPointer, ObjectKindPointer > PairOfKinds;
	typedef std::map< PairOfKinds, INTERACTION_TYPE > InteractionMap;
	typedef InteractionMap::iterator InteractionMapIterator;

	typedef std::list <Level> LevelList;
	typedef LevelList::iterator LevelListIterator;
	//typedef Mapping<Level> LevelMapping;

	void operator >> (const YAML::Node & options, ObjectKind &);

}

namespace graphics {
	void grid(const engine::Bound &, Color *);
}

namespace params {
	extern time_t last_menu_activity_time;
	extern int menu_timeout;
}

namespace lib {

	size_t strlen(const char *);
	template <typename T> std::string to_string (T);
	void stage(const char *);

}

struct Menu;
//class BitmapImage;

extern engine::Screen screen;
extern engine::Game game;
extern engine::Program program;
extern Menu menu;
extern Menu common_menu;
//extern std::stack<Menu *> menus;
//extern BitmapImage opening; // TODO: remove namespace image and name it properly
