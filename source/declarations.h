#ifndef DECLARATIONS_H
#define DECLARATIONS_H 1

typedef unsigned int positive;

namespace lib {
	template <typename Type> class List;
}

namespace sgl {
	void square();
	void draw_at(int, int, void(*)());
}

namespace gml {
	class Position;
	class Object;
	class Placement;
	class Game;
	class Field;
	class Area;
	class Shape;
}

#endif
