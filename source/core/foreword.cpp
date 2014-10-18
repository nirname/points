#include "foreword.hpp"

#include <string>
#include <list>
#include <cstdlib>

#include "options.hpp"
#include "directory.hpp"
#include "file.hpp"
#include "opengl.hpp"
#include "shape.hpp"

#include <iostream>

Foreword::Foreword() {
	loaded = false;
}

bool Foreword::filter(dirent * entry) {
	return file::has_extension(entry->d_name, "bmp");
}

bool Foreword::choose_random_image() {
	std::list<std::string> images;
	if(directory::read(options::foreword_images_directory.c_str(), DT_REG, images, filter)) {
		if(!images.empty()) {
			std::list<std::string>::iterator i = images.begin();
			int k = rand() % (images.size() - 2);
			while(k != 0) {
				i++;
				k--;
			}
			image_name = options::foreword_images_directory + *i;
			std::cout << "{ image_name: " << image_name << " } " << std::ends;
			return true;
		}
	}
	return false;
}

bool Foreword::load() {
	std::cout << "Foreword loading: " << std::ends;
	loaded = false;
	if(choose_random_image()) {
		loaded = input.ReadFromFile(image_name.c_str());
	} else {
		std::cout << "no" << std::endl;
		//graphics::write(std::string("Foreword: no image"));
	}
	std::cout << "ok" << std::endl;
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
					default_shape();
				glPopMatrix();
			glPopAttrib();
		}
	}
}

void Foreword::display() {
	if(loaded) {
		draw_image();
	} else {
		//graphics::write(qq);
	}
}

// show all colors immidiately
void Foreword::skip() {}
