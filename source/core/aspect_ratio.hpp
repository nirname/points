#pragma once

struct AspectRatio {
	unsigned int width, height;

	AspectRatio();
	AspectRatio(unsigned int _width, unsigned int _height);

	float aspect() const;
};
