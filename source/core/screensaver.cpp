#include "screensaver.hpp"

#include "drawing.hpp"
#include "library.hpp"
#include "emitter.hpp"


SCREENSAVER_KIND & operator ++ (SCREENSAVER_KIND & screensaver_kind, int) {
	int i = static_cast<int>(screensaver_kind);
	screensaver_kind = static_cast<SCREENSAVER_KIND>((i == 0)? 1 : i << 1);
	return screensaver_kind;
}

void Screensaver::display() {
	draw_text(to_string(kind));
}

void Screensaver::skip() {}

Queens::Queens() {
	size = 8; //std::rand() %
	width = height = size;
	field = new int[size];
}

Queens::~Queens() {
	delete [] field;
}

void Queens::display() {
	draw_text("QQQQ");
}
