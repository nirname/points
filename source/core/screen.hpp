#pragma once

struct AspectRatio {
	int width;
	int height;

	AspectRatio();
	AspectRatio(int _width, int _height);

	float aspect() const;

};

struct Screen {

	float width, height;

	Screen();
	Screen(float _width, float _height);

	void set(float _width, float _height);
	void set(float _height, const AspectRatio & aspect_ratio);
	void set_coordinates();
	void adjust(int lines);

};
