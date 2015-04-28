#include "handlers.hpp"

#include "variables.hpp"

/// GLUT keyboard function
void keyboard(unsigned char key, int x, int y) {
	application.handle(key, 0);
}

/// GLUT keyboard function for special keys
/**
	Special keys are:<br/>
		- GLUT_KEY_F1, GLUT_KEY_F2, ..., GLUT_KEY_F12 - F1 through F12 keys<br/>
		- GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN - Page Up and Page Down keys<br/>
		- GLUT_KEY_HOME, GLUT_KEY_END - Home and End keys<br/>
		- GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN - Arrow keys<br/>
		- GLUT_KEY_INSERT - Insert key
*/
void special(int special_key, int x, int y) {
	application.handle(0, special_key);
}

/// GLUT mouse function
void mouse(int button, int state, int width, int height) {}
