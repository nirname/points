#ifndef MENU_H
#define MENU_H 1

void draw_string(std::string & string) {
	for (std::string::iterator i = string.begin(); i != string.end(); ++i) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *i);
	}
}

float stroke_length(std::string & string) {
	float length = 0;
	for (std::string::iterator i = string.begin(); i != string.end(); ++i) {
		length += glutStrokeWidth(GLUT_STROKE_ROMAN, *i);
	}
	return length;
}

struct Menu {

	typedef Menu * MenuPointer;
	typedef std::list<MenuPointer> ItemsList;

	std::string name;
	ItemsList items;
	ItemsList::iterator current_item;

	Menu(std::string _name):
		name(_name)
	{
		current_item = items.begin();
	}

	~Menu() {
		for(ItemsList::iterator i = items.begin(); i != items.end(); ++i) {
			delete (*i);
		}
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
				for(ItemsList::iterator i = items.begin(); i != items.end(); ++i) {
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


	glPushAttrib(GL_CURRENT_BIT);
	glColor3ub(SOFT_BLUE);

	glPushMatrix();
	glTranslatef(10, 0, 0);
	const int h = 7, w = 5;
	const int z = 2;
	/*bool a[h][w] = {
		{1, 0, 0, 0, 1},
		{1, 1, 0, 1, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
	}; // M */
	bool a[h][w] = {
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
	}; // A
	//for(int y = h-1; y >= 0; y--) {
	for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			if(a[y][x] == 1) {
				//point(x, (h-y-1)); // original size
				point(x*z, (h-y-1)*z); // expanded size
				for(int sx = 0; sx < z; sx++) {
					//point(x*z + sx, (h-y-1)*z + sx); // diagonal
					//point(x*z + sx, (h-y-1)*z); // IBM style, horizontal striped
					//point(x*z, (h-y-1)*z + sx); // vertical striped
					/*for(int sy = 0; sy < z; sy++) {
						point(x*z + sx, (h-y-1)*z + sy); // scaled
					}*/
				}
			}
		}
	}
	/*point(0, 0); point(0, 1); point(0, 2); point(0, 3); point(0, 4); point(0, 5); point(0, 6);
	point(1, 5); point(2, 4); point(3, 5);
	point(4, 0); point(4, 1); point(4, 2); point(4, 3); point(4, 4); point(4, 5); point(4, 6);*/
	glPopMatrix();
	glPopAttrib();

	//graphics::grid(engine::Point(screen.width, screen.height));

}


#endif
