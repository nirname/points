#pragma once

namespace engine {

	/// Describes size by specifying length for each dimension
	//
	struct Size {

		/// Width of an object
		int width;
		/// Height of an object
		int height;

		/// Constructor with default values 1 and 1
		Size(int _width = 1, int _height = 1);

	};

	Size::Size(int _width, int _height):
		width(_width), height(_height)
	{}

}
