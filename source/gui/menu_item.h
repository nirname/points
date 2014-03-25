#pragma once

void MenuItem::handle(unsigned char key, int special_key, Interface * interface, Menu * menu) {
	std::cout << " ~ " << title;
	if(key == ENTER_KEY) {
		if(next_menu != interface->menus.end()) {
			interface->set_current_menu(next_menu);
		}
		if(handler != NULL) {
			handler(this);
		}
	}
}

void MenuItem::display(int position) {
	if(displayer != NULL) {
		displayer(position, this);
	} else {
		graphics::write(" * " + title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
	}
}
