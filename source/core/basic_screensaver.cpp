#include "basic_screensaver.hpp"

#include "drawing.hpp"

BasicScreensaver::BasicScreensaver() {}
BasicScreensaver::~BasicScreensaver() {}

void BasicScreensaver::display() {
	draw_text("Basic screensaver");
}
