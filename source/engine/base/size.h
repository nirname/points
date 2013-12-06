#ifndef SIZE_H
#define SIZE_H 1

namespace engine {

	struct Size {
		int width;
		int height;
		Size(int _width = 1, int _height = 1):
			width(_width), height(_height)
		{}
	};

}

#endif
