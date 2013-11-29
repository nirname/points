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
	std::string name;
	typedef std::list<Menu *> ItemsList;
	ItemsList items;

	Menu(std::string _name):
		name(_name)
	{}

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
}

void Menu::display_name() {
	glPushMatrix();
		glTranslatef(screen.width / 2, 0, 0);
		glScalef(0.1, 0.1, 0);
		glTranslatef(-stroke_length(name) / 2, 0, 0);
		glLineWidth(3);
			draw_string(name);
		glLineWidth(1);
	glPopMatrix();
}

void Menu::display() {
	//unsigned const char * c = (unsigned const char *)"Titres";
	//float s = screen.width / glutStrokeLength(GLUT_STROKE_ROMAN, c);
	glPushMatrix();
		glTranslatef(0, screen.height - 20, 0);
		display_name();
	glPopMatrix();
	glPushMatrix();
		glScalef(0.5, 0.5, 0);
		int y = 10;
		for(ItemsList::iterator i = items.begin(); i != items.end(); ++i) {
			y += 20;
			glPushMatrix();
				glTranslatef(0, screen.height - 20 - y, 0);
				(*i)->display_name();
			glPopMatrix();
		}
	glPopMatrix();

}


#endif
