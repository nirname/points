#pragma once

struct AspectRatio {
	int width, height;

	AspectRatio();
	AspectRatio(int _width, int _height);

	float aspect() const;
};

struct Screen {

	int width, height;

	Screen();
	Screen(int _width, int _height);

	void set(int _width, int _height);
	void set(int _height, const AspectRatio & aspect_ratio);
	void set_coordinates();
	void adjust(int _height);

};
