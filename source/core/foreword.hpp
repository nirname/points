#pragma once

#if defined(_WIN32) && defined(__GNUC__)
	#include "dirent/windows/dirent.h"
#elif defined(__linux__) && defined(__GNUC__)
	#include "dirent/linux/dirent.h"
#endif

#include "easy-bmp/EasyBMP.h"

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

};
