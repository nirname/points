#pragma once


// TODO: refactor this class
//struct Menu;

typedef Menu * MenuPointer;
typedef std::list<MenuPointer> MenusList;

typedef Mapping<Menu> MenuMapping;

struct Menu {

	// TODO: menu can be animated
	std::string name; // TODO: do not remove this attribute; rename to title?
	MenusList items;
	// TODO: replace it with mapping;
	MenusList::iterator current_item;

	Menu() {}

	Menu(std::string _name):
		name(_name)
	{
		current_item = items.begin();
	}

	void qq() {
		std::cout << ": " << this->name;
	}

	void process(unsigned char key) {
		if(current_item != items.end()) {
			(*current_item)->qq();
		} else {
			std::cout << ": no current item";
		}
	}

	~Menu() {
		/*for(MenusList::iterator i = items.begin(); i != items.end(); ++i) {
			try {
				delete (*i);
			} catch {
			}
		}*/
	}

	void display_name();
	void display();
	void add(Menu *);

//void Add(MenuNode * new_node);
//std::vector<MenuNode *> children; // changed to vector to preserve order
};

void Menu::add(Menu * item) {
	items.push_back(item);
	/*if(current_item == items.begin()) {
		current_item++;
	}*/
}

void Menu::display_name() {
	glPushMatrix();
		glScalef(0.1, 0.1, 0);
		glTranslatef(-stroke_length(name) / 2.0, 0, 0);
		//glTranslatef(0, -glutStrokeHeight(GLUT_STROKE_ROMAN), 0);
		//glTranslatef(0, -20, 0);
		//glLineWidth(2);
			draw_string(name);
		//glLineWidth(1);
	glPopMatrix();
}

void point(int x, int y) {
	glPushMatrix();
		glTranslatef(x, y, 0);
		graphics::square();
	glPopMatrix();
}

void Menu::display() {

	float font_height = 10;

	glPushMatrix();

		glPushMatrix();
			glPushAttrib(GL_CURRENT_BIT);
				glColor3ub(SOFT_BLUE);
				glRectf(0, screen.height - font_height * 3, screen.width, screen.height);
			glPopAttrib();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(screen.width / 2.0, screen.height - font_height * 2, 0);
			glPushAttrib(GL_CURRENT_BIT);
				glColor3ub(WHITE);
				display_name();
			glPopAttrib();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(screen.width / 2.0, screen.height / 2.0, 0);

			glPushMatrix();
				glScalef(0.5, 0.5, 0);

				glTranslatef(0, font_height * 2 * items.size() / 2, 0);
				for(MenusList::iterator i = items.begin(); i != items.end(); ++i) {
					//glPushMatrix();
					glPushAttrib(GL_CURRENT_BIT);
						if(i == menu.current_item) {
							glColor3ub(SOFT_BLUE);
						}
						glTranslatef(0, -font_height * 2, 0);
						(*i)->display_name();
					//glPopMatrix();
					glPopAttrib();
				}

			glPopMatrix();

		glPopMatrix();

	glPopMatrix();

}

// TODO: add menu manager
struct MenuManager {

	MenuMapping menus;
	std::stack<MenuPointer> stack;
	//MenusList menus;

	/*~MenuManager() {
		for(MenusList::iterator i = menus.begin(); i != menus.end(); ++i) {
			delete (*i);
		}
	}/**/

	void add() {

	}

};
