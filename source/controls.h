#ifndef VARIABLES_H
#define VARIABLES_H 1

#if defined(_WIN32) && defined(__GNUC__)
	#define ESCAPE_KEY VK_ESCAPE
#elif defined(__linux__) && defined(__GNUC__)
	#define ESCAPE_KEY 0x1B
#endif
//#define LEFT_KEY   0x25
//#define UP_KEY     0x26
//#define RIGHT_KEY  0x27
//#define DOWN_KEY   0x28

//GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN

//#endif

namespace controls {

	void keyboard(unsigned char key, int x, int y)
	{
		//std::cout << key << std::endl;
		switch(key)
		{
			case ESCAPE_KEY:
				exit(EXIT_SUCCESS);
				break;
			case 'w':
				offset_y--;
				glutPostRedisplay();
				break;
			case 's':
				offset_y++;
				glutPostRedisplay();
				break;
			case 'a':
				offset_x--;
				glutPostRedisplay();
				break;
			case 'd':
				offset_x++;
				glutPostRedisplay();
				break;
			case 'q':
				scale +=0.1;
				break;
			case 'e':
				if(scale > 0.1) scale -=0.1;
				break;
			default:
				std::cout << key << std::endl;
				break;
		}
	}

	/* Callbacks for special keys, such as:
	GLUT_KEY_F1, GLUT_KEY_F2, ..., GLUT_KEY_F12 - F1 through F12 keys
	GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN - Page Up and Page Down keys
	GLUT_KEY_HOME, GLUT_KEY_END - Home and End keys
	GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN - Arrow keys
	GLUT_KEY_INSERT - Insert key */
	void special(int key, int x, int y)
	{
		switch(key)
		{
			case GLUT_KEY_UP:
				offset_y--;
				glutPostRedisplay();
				break;
			case GLUT_KEY_DOWN:
				offset_y++;
				glutPostRedisplay();
				break;
			case GLUT_KEY_LEFT:
				offset_x--;
				glutPostRedisplay();
				break;
			case GLUT_KEY_RIGHT:
				offset_x++;
				glutPostRedisplay();
				break;
			default:
				std::cout << key << std::endl;
				break;
		}
	}

	void mouse(int button, int state, int width, int height)
	{
	}
}

#endif
