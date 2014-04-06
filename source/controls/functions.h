#pragma once

namespace controls {

	void keyboard(unsigned char key, int x, int y) {
		glutPostRedisplay(); // TODO: for dubug, remove it
		application.handle(key, 0);
	}

	/* Callbacks for special keys, such as:
	GLUT_KEY_F1, GLUT_KEY_F2, ..., GLUT_KEY_F12 - F1 through F12 keys
	GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN - Page Up and Page Down keys
	GLUT_KEY_HOME, GLUT_KEY_END - Home and End keys
	GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN - Arrow keys
	GLUT_KEY_INSERT - Insert key */

	void special(int special_key, int x, int y) {
		glutPostRedisplay();
		application.handle(0, special_key);
	}

	void mouse(int button, int state, int width, int height) {
	}

}
