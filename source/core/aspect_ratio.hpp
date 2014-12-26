#pragma once

struct AspectRatio {
	int width, height;

	AspectRatio();
	AspectRatio(int _width, int _height);

	float aspect() const;
};
