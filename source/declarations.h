#ifndef DECLARATIONS_H
#define DECLARATIONS_H 1

typedef unsigned int positive;

namespace lib {
	//template <typename Type> class List;
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
	struct Placement;

	typedef Field  * FieldPointer;
	typedef View   * ViewPointer;
	typedef Object * ObjectPointer;
	typedef Point  * PointPointer;

	typedef std::string KeyType;
	//typedef const char * KeyType;
	typedef std::map< KeyType, FieldPointer  > FieldMap;
	typedef std::map< KeyType, ViewPointer   > ViewMap;
	typedef std::map< KeyType, ObjectPointer > ObjectMap;

	typedef std::map< Placement, PointPointer > PointMap;

	typedef std::map< KeyType, graphics::ColorPointer > ColorMap;
	typedef std::map< KeyType, graphics::ShapePointer > ShapeMap;

}

extern engine::Screen screen;
extern engine::Game game;

#endif
