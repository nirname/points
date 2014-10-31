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

bool Foreword::choose_random_image() {
	std::list<std::string> images;
	if(directory::read(options::images_directory.c_str(), DT_REG, images, filter)) {
		if(!images.empty()) {
			std::list<std::string>::iterator i = images.begin();
			int k = rand() % (images.size() - 2);
			while(k != 0) {
				i++;
				k--;
			}
			image_name = options::images_directory + *i;
			std::cout << image_name << std::endl;
			return true;
		}
	}
	return false;
}

bool Foreword::load() {
	std::cout << "* Foreword: " << std::ends;
	loaded = false;
	if(choose_random_image()) {
		loaded = input.ReadFromFile(image_name.c_str());
		//base = glGenLists(1);
		//glNewList(base, GL_COMPILE);
		draw_image();
		//glEndList();
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
					draw_block();
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
