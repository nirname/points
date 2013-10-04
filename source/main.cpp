#include "global.h"

engine::Screen screen(22.0, 22.0); // move screen to game?
engine::Game game(logic::SOKOBAN);

void hello() {
	std::cout << "Hello" << std::endl;
}

int main(int argc, char * argv[])
{
	std::cout << std::endl;
	std::cout << "Points" << std::endl;
	std::cout << "Independent Games" << std::endl;
	std::cout << "Arcades, Puzzles & Traditional games" << std::endl;
	std::cout << "Author: Nicolay Rozhkov" << std::endl;

	// initialize glut
	glutInit(&argc, argv);

	//graphics::load_palette();

	lib::stage("LOADING PARAMETERS");

	params::load();

	lib::stage("INITIALIZING GRAPHICS");

	//game.fields.erase("qq");
	//std::cout << *game.get_field("Field") << std::endl;
	//std::cout << *game.get<engine::FieldPointer>(std::string("Field")) << std::endl;
	//game.component_by_type<engine::View *>();
	//std::cout << * game.get<engine::Field *>("Field") << std::endl;

	/*std::cout << "red: "   << glutGetColor(12, GLUT_RED)   << std::endl;
	std::cout << "green: " << glutGetColor(12, GLUT_GREEN) << std::endl;
	std::cout << "blue: "  << glutGetColor(12, GLUT_BLUE)  << std::endl;*/

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

	glShadeModel(GL_SMOOTH);    // Разрешить плавное сглаживание
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);

	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Сглаживание линий
	//glEnable(GL_BLEND);         // Разрешить смешивание
	//glEnable(GL_LINE_SMOOTH);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(BLACK, 0.0f);
	glClearDepth(1.0f);

	//glMatrixMode(GL_PROJECTION);
	//glMatrixMode(BASE_MATRIX_MODE);
	glLoadIdentity();
	gluOrtho2D(0.0, screen.width, 0.0, screen.width);
	//glOrtho2(0.0, screen.width, 0.0, screen.width, -1.0, 1.0);

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

	game.load();
	//std::cout << "\nTest\n" << game.attribute("fields")["field"] << std::endl;

	lib::stage("STARTING GAME\n");

	// main loop
	glutMainLoop();

	//system("PAUSE");

	return EXIT_SUCCESS;
}
