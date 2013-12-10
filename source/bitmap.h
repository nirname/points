#pragma once

class BitmapImage {

	bitmap_image * image;

	public:

	BitmapImage() : image(NULL) {
	}

	void close() {
		delete image;
		image = NULL;
	}

	~BitmapImage() {
		close();
	}

	void open(const std::string & file_name) {
		close();
		image = new bitmap_image(file_name);
		std::cout << "open image" << !(*image) << std::endl;
	}

	void display() {
		if(image == NULL || !(*image)) {
			return;
		}

		unsigned char red, green, blue;

		const unsigned int width  = image->width();
		const unsigned int height = image->height();

		for (std::size_t y = 0; y < height; ++y) {
			for (std::size_t x = 0; x < width; ++x) {
				image->get_pixel(x, y, red, green, blue);
				glPushAttrib(GL_CURRENT_BIT);
					glColor3ub(red, green, blue);
					glPushMatrix();
						glTranslatef(x, height - 1 - y, 0);
						graphics::square();
					glPopMatrix();
				glPopAttrib();
			}
		}

	}


};
