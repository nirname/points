#ifndef DECLARATIONS_H
#define DECLARATIONS_H 1

typedef unsigned int positive;

float scale = 1.0;

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
}

namespace engine {

	struct Screen;
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

	typedef std::string KeyType;
	typedef std::string ObjectKindType;

	typedef std::map< KeyType, FieldPointer  > FieldMap;
	typedef std::map< KeyType, ViewPointer   > ViewMap;
	typedef std::map< KeyType, ObjectPointer > ObjectMap;

	typedef std::map< KeyType, graphics::ColorPointer > ColorMap;
	typedef std::map< KeyType, graphics::ShapePointer > ShapeMap;

	typedef std::map< Object *, Point > ObjectsInformation;
	typedef std::map< Point, Object * > PointsInformation;

	typedef ObjectsInformation::iterator ObjectsInformationIterator;
	typedef PointsInformation::iterator PointsInformationIterator;

	enum INTERACTION_TYPE {
		PUSH_INTERACTION,
		DESTROY_INTERACTION,
		CREATE_INTERACTION
	};

	typedef std::pair< ObjectKindType, ObjectKindType > PairOfKinds;
	typedef std::map< PairOfKinds, INTERACTION_TYPE > InteractionMap;
	typedef InteractionMap::iterator InteractionMapIterator;

}

extern engine::Screen screen;
extern engine::Game game;

#endif
