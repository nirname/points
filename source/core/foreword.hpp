#pragma once

#include "easy_bmp.hpp"
#include "dirent.hpp"
#include "opengl.hpp"

struct Foreword {

	BMP input;
	bool loaded;
	GLuint base;
	std::string image_name;

	Foreword();
	~Foreword();

	static bool filter(dirent * entry);

	bool choose_random_image();
	bool load();
	void draw_image();
	void display();

	void skip();

};
