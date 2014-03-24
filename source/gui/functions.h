#pragma once

void quit() {
	std::cout << " -> quit";
	std::cout << std::endl;
	exit(EXIT_SUCCESS);
}

void display_option(int position, MenuItem * _menu_item) {
	graphics::write(" (option) * " + _menu_item->title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
}
