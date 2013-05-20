#ifndef DECLARATIONS_H
#define DECLARATIONS_H 1

typedef unsigned int positive;

namespace lib {
	template <typename Type> class List;
}

namespace graphics {
	void square();
	struct Color;
	struct Shape;
}

namespace logic {}

namespace engine {

	struct Object;
	struct Game;
	struct Point;
	struct Size;
	struct Field;
	struct Screen;
	struct View;
	struct Placement;

	typedef std::string KeyType;
	typedef std::map< KeyType, engine::Field * >   FieldMap;
	typedef std::map< KeyType, engine::View * >    ViewMap;
	typedef std::map< KeyType, engine::Object * >  ObjectMap;
	typedef std::map< KeyType, graphics::Color * > ColorMap;
	typedef std::map< KeyType, graphics::Shape * > ShapeMap;
	typedef std::map< Placement, Point > PointMap;

}

extern engine::Screen screen;
extern engine::Game game;

#endif
