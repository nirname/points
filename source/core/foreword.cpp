#include "foreword.hpp"

#include <string>
#include <list>
#include <cstdlib>

#include "options.hpp"
#include "directory.hpp"
#include "file.hpp"
#include "opengl.hpp"
#include "shape.hpp"
#include "drawing.hpp"

#include <iostream>

std::list<std::string> Foreword::images;

Foreword::Foreword() {
	loaded = false;
	base = 0;
}

Foreword::~Foreword() {
	//glDeleteLists(base, 1);
}

bool Foreword::filter(dirent * entry) {
	return file::has_extension(entry->d_name, "bmp");
}

bool Foreword::load_images_list(bool force) {
	if(force || images.empty()) {
		if(directory::read(options::images_directory.c_str(), DT_REG, images, filter)) {
			images.sort();
			return !images.empty();
		}
		return false;
	}
	return true;
}

bool Foreword::choose_random_image(std::string & _image_name) {
	if(load_images_list()) {
		std::list<std::string>::iterator i = images.begin();
		int k = rand() % (images.size() - 2);
		while(k != 0) {
			i++;
			k--;
		}
		_image_name = options::images_directory + *i;
		std::cout << _image_name << std::endl;
		return true;
	}
	return false;
}

/// Loads an image
//
/// Loads an image from images directory or from the argument given.
/// If argument is empty, than random image will be choosen.
/// Full image path is required.
///
bool Foreword::load(std::string _image_name) {
	std::cout << "* Foreword: " << std::ends;
	loaded = false;
	image_name = _image_name;
	if(!image_name.empty() || choose_random_image(image_name)) {
		std::cout << image_name << std::endl;
		loaded = input.ReadFromFile(image_name.c_str());
		//base = glGenLists(1);
		//glNewList(base, GL_COMPILE);
		draw_image();
		//glEndList();
	} else {
		std::cout << "skipped" << std::endl;
	}
	return loaded;
}

// Draw different colors separately
//
void Foreword::draw_image() {
	RGBApixel * pixel;
	for(int x = 0; x < input.TellWidth(); x++) {
		for(int y = 0; y < input.TellHeight(); y++) {
			glPushAttrib(GL_CURRENT_BIT);
				pixel = input(x, y);
				glColor3ub(pixel->Red, pixel->Green, pixel->Blue);
				glPushMatrix();
					glTranslatef(x, input.TellHeight() - 1 - y, 0);
					default_shape.display();
				glPopMatrix();
			glPopAttrib();
		}
	}
}

void Foreword::display() {
	if(loaded) {
		draw_image();
		//glCallList(base);
	} else {
		write(std::string("Foreword"));
	}
}

// show all colors immidiately
void Foreword::skip() {}
