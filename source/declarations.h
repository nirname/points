#ifndef DECLARATIONS_H
#define DECLARATIONS_H 1

typedef unsigned int positive;

namespace lib {
	template <typename Type> class List;
}

namespace graphics {
	void square();
	void draw_at(int, int, void(*)());
}

namespace logic {
	class Game;
}

namespace engine {

	class Point;
	class Size;
	class Field;
	class Screen;
	class View;

}

#endif
