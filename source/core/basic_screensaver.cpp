#include "basic_screensaver.hpp"

#include "drawing.hpp"

BasicScreensaver::BasicScreensaver() {
	size = Size(12, 12);
}

BasicScreensaver::~BasicScreensaver() {}

void BasicScreensaver::display() {
	draw_text("Basic screensaver");
}
