#pragma once

#define SMALL_ASPECT 54

#define SCREEN_FORMAT_4x3   72, SMALL_ASPECT
#define SCREEN_FORMAT_3x2   81, SMALL_ASPECT
#define SCREEN_FORMAT_14x9  84, SMALL_ASPECT
#define SCREEN_FORMAT_16x9  96, SMALL_ASPECT
#define SCREEN_FORMAT_1_85 100, SMALL_ASPECT
#define SCREEN_FORMAT_2_39 129, SMALL_ASPECT

struct Screen {

	float width, height;

	Screen();
	Screen(float _width, float _height);

	void set(float _width, float _height);
	void adjust();

};
