#pragma once

namespace engine {

	struct Size {

		int width;
		int height;

		Size(int _width = 1, int _height = 1);

	};
	
	Size::Size(int _width, int _height):
		width(_width), height(_height)
	{}

}


