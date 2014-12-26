#include "aspect_ratio.hpp"

AspectRatio::AspectRatio() :
	width(16), height(9)
{}

AspectRatio::AspectRatio(int _width, int _height) :
	width(_width), height(_height)
{}

float AspectRatio::aspect() const {
	return (float)width / (float)height;
}
