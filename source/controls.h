#ifndef VARIABLES_H
#define VARIABLES_H 1

#if defined(_WIN32) && defined(__GNUC__)
	#define ESCAPE_KEY VK_ESCAPE
#elif defined(__linux__) && defined(__GNUC__)
	#define ESCAPE_KEY 0x1B
#endif

namespace controls {

	void keyboard(unsigned char key, int x, int y)
	{
		engine::Point position;
		engine::Point offset;
		graphics::ANIMATION_TYPE animation_type = graphics::NONE;
		switch(key)
		{
			case ESCAPE_KEY: exit(EXIT_SUCCESS); break;
			case '8': position = engine::Point( 0,  1); break;
			case '5': position = engine::Point( 0, -1); break;
			case '4': position = engine::Point(-1,  0); break;
			case '6': position = engine::Point( 1,  0); break;
			case 'w': offset   = engine::Point( 0,  1); break;
			case 's': offset   = engine::Point( 0, -1); break;
			case 'a': offset   = engine::Point(-1,  0); break;
			case 'd': offset   = engine::Point( 1,  0); break;
			case 'x': animation_type = graphics::FADE; break;
			default: std::cout << "free: ";
		}
		game.views[std::string("View")]->position += position;
		game.views[std::string("View")]->offset += offset;
		//game.objects[std::string("Sokoban")];
		std::cout << key << std::endl;
		//glutPostRedisplay();
	}

	/* Callbacks for special keys, such as:
	GLUT_KEY_F1, GLUT_KEY_F2, ..., GLUT_KEY_F12 - F1 through F12 keys
	GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN - Page Up and Page Down keys
	GLUT_KEY_HOME, GLUT_KEY_END - Home and End keys
	GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN - Arrow keys
	GLUT_KEY_INSERT - Insert key */
	void special(int key, int x, int y)
	{
		engine::Field * field = game.fields[std::string("Field")];
		engine::Object * sokoban = game.objects[std::string("Sokoban")];
		engine::Point step;
		switch(key)
		{
			case GLUT_KEY_UP:    step = engine::Point( 0,  1); break;
			case GLUT_KEY_DOWN:  step = engine::Point( 0, -1); break;
			case GLUT_KEY_LEFT:  step = engine::Point(-1,  0); break;
			case GLUT_KEY_RIGHT: step = engine::Point( 1,  0); break;
		}
		sokoban->move(field, step);
		//glutPostRedisplay();
		std::cout << key << std::endl;
	}

	void mouse(int button, int state, int width, int height)
	{
	}
}

#endif
