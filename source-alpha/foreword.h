#pragma once

namespace Foreword {

	BMP input;
	bool loaded = false;
	std::string qq;

	bool filter(dirent * entry) {
		return File::has_extension(entry->d_name, "bmp");
	}

	bool choose_random_image(std::string & _image_name) {
		lines images;
		if(Directory::read("../images/ornament", DT_REG, images, filter)) {
			if(!images.empty()) {
				lines::iterator i = images.begin();
				int k = rand() % (images.size() - 2);
				while(k != 0) {
					i++;
					k--;
				}
				_image_name = std::string("../images/ornament/") + *i;
				qq = _image_name;
				return true;
			}
		}
		return false;
	}

	bool load() {
		loaded = false;
		std::string image_name;
		if(choose_random_image(image_name)) {
			loaded = input.ReadFromFile(image_name.c_str());
		} else {
			//graphics::write(std::string("Foreword: no image"));
		}
		return loaded;
	}

	void draw_image() {
		RGBApixel * pixel;
		for(int x = 0; x < input.TellWidth(); x++) {
			for(int y = 0; y < input.TellHeight(); y++) {
				glPushAttrib(GL_CURRENT_BIT);
					pixel = input(x, y);
					glColor3ub(pixel->Red, pixel->Green, pixel->Blue);
					glPushMatrix();
						glTranslatef(x, input.TellHeight() - 1 - y, 0);
						graphics::default_shape();
					glPopMatrix();
				glPopAttrib();
			}
		}
	}

	void display() {
		if(loaded) {
			draw_image();
		} else {
			graphics::write(qq);
		}
	}

}
