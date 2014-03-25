#pragma once

void MenuItem::handle(unsigned char key, int special_key, Interface * interface, Menu * menu) {
	std::cout << " ~ " << title;
	if(key == ENTER_KEY) {
		if(next_menu != interface->menus.end()) {
			interface->set_current_menu(next_menu);
		}
		if(handler != NULL) {
			handler();
		}
	}
}

void MenuItem::display(int position) {
	if(custom_display != NULL) {
		custom_display(position, this);
	} else {
		graphics::write(" * " + title, 0, position * glutBitmapHeight(GLUT_BITMAP_9_BY_15));
	}
}
