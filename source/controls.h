#ifndef VARIABLES_H
#define VARIABLES_H 1

/*#if defined(_WIN32) && defined(__GNUC__)
	#define ESCAPE_KEY VK_ESCAPE
#elif defined(__linux__) && defined(__GNUC__)
	#define ESCAPE_KEY 0x1B
#endif*/

#define ESCAPE_KEY 27

struct EntityIdentifier {
	const char * entity_kind;
	std::string entity_name;
};

namespace controls {

	enum ACTION_NAME {
		MOVE
	};

	/*class Action {
		ACTION_NAME name;
		std::list<engine::Point> options;
	};*/

	struct ActionOptions {
		std::list<engine::Point> points;
		std::list<EntityIdentifier> entities;
	};

	class ControlHandler {
		Mapping<ActionOptions> actions; // actions with it's options
		std::list<EntityIdentifier> entities;
	};


	void keyboard(unsigned char key, int x, int y)
	{
		printf("%i", key);
		if(key == ESCAPE_KEY) {
			std::cout << ": quit" << std::endl;
			exit(EXIT_SUCCESS);
		}
		if(key == 'p') {
			game.paused = !game.paused;
			if(game.paused) {
				std::cout << ": pause";
			}
			else {
				std::cout << ": resume";
				glutTimerFunc(0, image::redisplay, 0);
			}
		}
		if(!game.paused) {
			engine::Point position;
			engine::Point offset;
			//graphics::ANIMATION_TYPE animation_type = graphics::NO_ANIMATION;
			switch(key)
			{
				case '8': position = engine::Point( 0,  1); break;
				case '5': position = engine::Point( 0, -1); break;
				case '4': position = engine::Point(-1,  0); break;
				case '6': position = engine::Point( 1,  0); break;
				case 'w': offset   = engine::Point( 0,  1); break;
				case 's': offset   = engine::Point( 0, -1); break;
				case 'a': offset   = engine::Point(-1,  0); break;
				case 'd': offset   = engine::Point( 1,  0); break;
				case 'p': break;
				// case 'x': animation_type = graphics::FADE_ANIMATION; break;
				default: std::cout << ": free";
			}
			// move all views
			//game.views[std::string("View")]->position += position;
			//game.views[std::string("View")]->offset += offset;
			//game.objects[std::string("Sokoban")];
			//std::cout << "Key: " << key << std::endl;
			glutPostRedisplay();
		}
		std::cout << std::endl;
	}

	/* Callbacks for special keys, such as:
	GLUT_KEY_F1, GLUT_KEY_F2, ..., GLUT_KEY_F12 - F1 through F12 keys
	GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN - Page Up and Page Down keys
	GLUT_KEY_HOME, GLUT_KEY_END - Home and End keys
	GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN - Arrow keys
	GLUT_KEY_INSERT - Insert key */

	engine::Point step;

	void move_sokoban() {
		game.objects[std::string("Sokoban")]->move(game.fields[std::string("Field")], step);
	}

	void special(int key, int x, int y)
	{
		if(!game.paused) {
			engine::Field * field = game.fields[std::string("Field")];
			engine::Object * sokoban = game.objects[std::string("Sokoban")];
			switch(key)
			{
				case GLUT_KEY_UP:    step = engine::Point( 0,  1); break;
				case GLUT_KEY_DOWN:  step = engine::Point( 0, -1); break;
				case GLUT_KEY_LEFT:  step = engine::Point(-1,  0); break;
				case GLUT_KEY_RIGHT: step = engine::Point( 1,  0); break;
			}
			//game.animations["Scale"]->do_after = move_sokoban;
			//game.animations["Scale"]->start();
			//, game.animations[std::string("Scale")]
			//sokoban->move(field, step);
			//sokoban->move(field, step);
			//std::cout << "Key: " << key << std::endl;
			//glutPostRedisplay();
			printf("%i", key);
			std::cout << std::endl;
		}
	}

	void mouse(int button, int state, int width, int height)
	{
	}
}

#endif
