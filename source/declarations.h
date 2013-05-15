#ifndef DECLARATIONS_H
#define DECLARATIONS_H 1

typedef unsigned int positive;

extern float offset_x, offset_y;
extern float scale;

namespace lib {
	template <typename Type> class List;
}

namespace graphics {
	void square();
	void draw_at(int, int, void(*)());
}

namespace logic {}

namespace engine {
	struct Game;
	struct Point;
	struct Size;
	struct Field;
	struct Screen;
	struct View;
}

extern engine::Screen screen;
extern engine::Game game;

/*extern std::unordered_map<std::string, engine::Point> points;

extern std::unordered_map<int, int> data;
extern std::set<int> line;

extern std::vector<int> kont;*/

#endif
