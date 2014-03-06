#pragma once

/*#if defined(_WIN32) && defined(__GNUC__)
	#define ESCAPE_KEY VK_ESCAPE
#elif defined(__linux__) && defined(__GNUC__)
	#define ESCAPE_KEY 0x1B
#endif*/

/*struct EntityIdentifier {
	const char * entity_kind;
	std::string entity_name;
};*/

/*class Action {
	ACTION_NAME name;
	std::list<engine::Point> options;
};*/

/*struct ActionOptions {
	std::list<engine::Point> points;
	std::list<EntityIdentifier> entities;
};*/

namespace controls {

	void keyboard(unsigned char key, int x, int y)
	{
		glutPostRedisplay(); // TODO: for dubug, remove it
		application.process(key);
	}

	/* Callbacks for special keys, such as:
	GLUT_KEY_F1, GLUT_KEY_F2, ..., GLUT_KEY_F12 - F1 through F12 keys
	GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN - Page Up and Page Down keys
	GLUT_KEY_HOME, GLUT_KEY_END - Home and End keys
	GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN - Arrow keys
	GLUT_KEY_INSERT - Insert key */

	engine::Point step;

	void special(int key, int x, int y)
	{
		//program.process(key);
	}

	void mouse(int button, int state, int width, int height)
	{
	}
}
