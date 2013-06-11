#ifndef DECLARATIONS_H
#define DECLARATIONS_H 1

typedef unsigned int positive;

float scale = 1.0;

typedef std::string KeyType;

namespace lib {
	//template <typename Type> class List;
}

namespace image {
	void redisplay(int);
}

namespace graphics {
	void square();
	struct Color;
	struct Shape;

	typedef Color * ColorPointer;
	typedef Shape * ShapePointer;

	struct Animation;
	typedef Animation * AnimationPointer;
	typedef std::map< KeyType, AnimationPointer > AnimationMap;
	typedef AnimationMap::iterator AnimationMapIterator;

}

namespace engine {

	struct Screen;
	struct Level;
	struct Game;
	struct Field;
	struct View;
	struct Object;
	struct Point;
	struct Size;

	typedef Field  * FieldPointer;
	typedef View   * ViewPointer;
	typedef Object * ObjectPointer;
	typedef Point  * PointPointer;

	typedef std::string ObjectKindType;

	typedef std::map< KeyType, FieldPointer  > FieldMap;
	typedef std::map< KeyType, ViewPointer   > ViewMap;
	typedef std::map< KeyType, ObjectPointer > ObjectMap;

	typedef std::map< KeyType, graphics::ColorPointer > ColorMap;
	typedef std::map< KeyType, graphics::ShapePointer > ShapeMap;

	typedef std::map< Object *, Point > ObjectInformation;
	typedef std::map< Point, Object * > PointInformation;

	typedef ObjectInformation::iterator ObjectInformationIterator;
	typedef PointInformation::iterator PointInformationIterator;

	enum INTERACTION_TYPE {
		PUSH_INTERACTION,
		PULL_INTERACTION,
		DESTROY_INTERACTION,
		CREATE_INTERACTION
	};

	typedef std::pair< ObjectKindType, ObjectKindType > PairOfKinds;
	typedef std::map< PairOfKinds, INTERACTION_TYPE > InteractionMap;
	typedef InteractionMap::iterator InteractionMapIterator;

	typedef std::list <Level> LevelList;
	typedef LevelList::iterator LevelListIterator;

}

extern engine::Screen screen;
extern engine::Game game;

#endif
