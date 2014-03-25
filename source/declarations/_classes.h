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

	struct Screen;

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

struct Screensaver;

namespace engine {

	struct Point;
	struct Size;
	struct Bound;

	struct Application;

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

	typedef std::pair< ObjectKindPointer, ObjectKindPointer > PairOfKinds;
	typedef std::map< PairOfKinds, INTERACTION_TYPE > InteractionMap;
	typedef InteractionMap::iterator InteractionMapIterator;

	typedef std::list<Level> LevelList;
	typedef LevelList::iterator LevelListIterator;
	//typedef Mapping<Level> LevelMapping;

	void operator >> (const YAML::Node & options, ObjectKind &);

}

namespace graphics {
	void grid(const engine::Bound & _bound, int _step = 1);
}

namespace lib {

	size_t strlen(const char *);
	template <typename T> std::string to_string (T);
	void stage(const char *);

}

struct Menu;
struct MenuItem;
struct Interface;
struct Screensaver;
