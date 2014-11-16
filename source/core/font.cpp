#include "font.hpp"
#include "easy_bmp.hpp"

#include "drawing.hpp"
#include "shape.hpp"
#include "options.hpp"

Font::Font() {
	base = 0;
	letters_count = 0;
}

Font::~Font() {
	glDeleteLists(base, letters_count);
}

void Font::load(const std::string & fonts_directory, const std::string & font_name) {
	std::cout << "Font: " << std::endl;
	std::cout << "  name: " << font_name << std::endl;
	std::string image_name = fonts_directory + font_name + ".bmp";

	BMP input;
	if(input.ReadFromFile(image_name.c_str())) {
		RGBApixel * pixel;
		width = 5;
		height = input.TellHeight();
		letters_count = input.TellWidth() / width;
		std::cout << "  letters_count: " << letters_count << std::endl;
		base = glGenLists(letters_count);
		std::cout << "  base: " << base << std::endl;
		for(int letter_id = 0; letter_id < letters_count; letter_id++) {
			glNewList(letter_id + base, GL_COMPILE);
				glPushMatrix();
					glTranslatef(0, height, 0);
					glScalef(1, -1, 1);
					int absolute_x = letter_id * width;
					for(int x = 0; x < width; x++ ) {
						for(int y = 0; y < height; y++) {
							pixel = input(x + absolute_x, y);
							if(pixel->Red == 0 && pixel->Green == 0 && pixel->Blue == 0) {
								glPushMatrix();
									glTranslatef(x, y, 0);
									default_shape.display();
								glPopMatrix();
							}
						}
					}
				glPopMatrix();
			glEndList();
		}
		std::cout << "ok" << std::endl;
	}

}
