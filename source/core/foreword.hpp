#pragma once

#include "easy_bmp.hpp"
#include "dirent.hpp"
#include "opengl.hpp"
#include <string>
#include <list>

struct Foreword {

	static std::list<std::string> images;

	static bool load_images_list(bool force = false);
	static bool filter(dirent * entry);

	BMP input;
	bool loaded;
	GLuint base;
	std::string image_name;

	Foreword();
	~Foreword();

	static bool choose_random_image(std::string & _image_name);
	bool load(std::string image_name = std::string(""));
	void draw_image();
	void display();

	void skip();

};
