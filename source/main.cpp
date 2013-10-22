#include "global.h"

engine::Screen screen(20, 20); // move screen to game?
engine::Game game;
PROGRAM_MODE mode = GAMEPLAY_MODE;
int graphics::sleep = 50;

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

	glClearColor(BLACK, 0.5f);
	glClearDepth(1.0f);

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);

	/*glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);

	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);

	*glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);*/

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);

	//glMatrixMode(GL_PROJECTION);
	//glMatrixMode(BASE_MATRIX_MODE);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, screen.width, 0.0, screen.height);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	/*glLoadIdentity();
	gluOrtho2D(0.0, screen.width, 0.0, screen.width);*/

	// drawing
	glutDisplayFunc(image::display);
	glutReshapeFunc(image::reshape);

	glutIdleFunc(image::idle);
	glutTimerFunc(graphics::sleep, image::redisplay, 0);

	// commands
	glutKeyboardFunc(controls::keyboard);
	glutSpecialFunc(controls::special);
	glutMouseFunc(controls::mouse);

	game.load();
	//std::cout << "\nTest\n" << game.attribute("fields")["field"] << std::endl;

	lib::stage("STARTING GAME\npress `p` to pause game\n");

	// main loop
	glutMainLoop();

	//system("PAUSE");

	return EXIT_SUCCESS;
}
