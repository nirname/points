#include "global.h"

float offset_x = 0, offset_y = 0;
float scale = 1;

engine::Screen screen(10.0, 10.0);
engine::Game game(logic::SOKOBAN);

/*std::unordered_map<std::string, engine::Point> points;
std::unordered_map<int, int> data;
std::set<int> line;*/

std::unordered_map<int, std::unordered_map<int, engine::Cell> > cells;

//std::vector<int> kont;

int main(int argc, char * argv[])
{
	//points["Player1"] = engine::Point(0, 2);
	//points["Player2"] = engine::Point(3, 1);
	//engine::Screen screen(10, 10);

	//data[0] = 0;
	//data[9] = 0;

	//line.insert(0);

	//kont;
	// uploading params from file
	params::upload_params();

	// initialize glut
	glutInit(&argc, argv);

	glutInitDisplayMode(params::display_mode);

	// set window parameters
	glutInitWindowSize(params::window_width, params::window_height);
	glutInitWindowPosition(0, 0);

	if(params::game_mode) {
		glutGameModeString(params::mode_string);
		glutEnterGameMode();
	} else {
		glutCreateWindow("Point Games");
		if(params::full_screen) {
			glutFullScreen();
		}
	}

	// creating game
	// testing inside display function

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glShadeModel(GL_SMOOTH);    // Разрешить плавное сглаживание
	//glClearColor(0.0f, 0.0f, 0.0f, 0.5f);   // Черный фон
	//glClearDepth(1.0f);         // Настройка буфера глубины
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Сглаживание линий
	//glEnable(GL_BLEND);         // Разрешить смешивание
	//glEnable(GL_LINE_SMOOTH);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, screen.width, 0.0, screen.width, -1.0, 1.0);
	//glOrtho(0.0, screen.size.width, 0.0, screen.size.height, -1.0, 1.0);

	// drawing
	glutDisplayFunc(image::display);
	glutReshapeFunc(image::reshape);

	glutIdleFunc(image::idle);
	glutTimerFunc(50, image::redisplay, 0);

	// commands
	glutKeyboardFunc(controls::keyboard);
	glutSpecialFunc(controls::special);
	glutMouseFunc(controls::mouse);

	// main loop
	glutMainLoop();

	//system("PAUSE");

	return EXIT_SUCCESS;
}
