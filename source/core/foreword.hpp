#pragma once

#include "easy-bmp/EasyBMP.h"
#include "dirent.hpp"

struct Foreword {

	BMP input;
	bool loaded;
	std::string image_name;

	Foreword();

	static bool filter(dirent * entry);

	bool choose_random_image();
	bool load();
	void draw_image();
	void display();

	void skip();

};
