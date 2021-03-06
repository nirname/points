#pragma once

#include "opengl.hpp"
#include <string>

struct Font {

	GLuint base; /// base of display lists
	int letters_count; /// count of letters in this font
	int width;
	int height;

	Font();
	~Font();
	void load(const std::string & fonts_directory, const std::string & font_name);

};
