#pragma once

struct AspectRatio {
	float width;
	float height;

	AspectRatio(float _width, float _height);

	float aspect() const;

};

struct Screen {

	float width, height;

	Screen();
	Screen(float _width, float _height);

	void set(float _width, float _height);
	void set(float _height, const AspectRatio & aspect_ratio);
	void set_coordinates();
	void adjust(float lines);

};
