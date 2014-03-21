#include "global.h"

// TODO: move all to params all variables
graphics::Screen screen(SCREEN_FORMAT_16x9);
engine::Game game; // TODO(!): use pointer here
engine::Application application;

Interface interface;

//BitmapImage opening;

int graphics::sleep = 50;

void hello() {
	std::cout << "Hello" << std::endl;
}

int main(int argc, char * argv[])
{

	std::cout << std::endl;
	std::cout << "Independent Logic Games" << std::endl;
	std::cout << "Arcades, Puzzles & Classical games" << std::endl;

	std::cout << std::endl;

	//for(int i = 32; i < 127; i++) {
	//	printf("%c", (char)i);
	//}
	
	//std::cout << argv[0] << std::endl;

	std::cout << lib::application_path() << std::endl;

	//Manager<int, std::string> m;

	//Directory::read("levels");

	//graphics::load_palette();

	lib::stage("INITIALIZING");

	params::load();
	params::print();

	//std::cout << "red: "   << glutGetColor(12, GLUT_RED)   << std::endl;
	//std::cout << "green: " << glutGetColor(12, GLUT_GREEN) << std::endl;
	//std::cout << "blue: "  << glutGetColor(12, GLUT_BLUE)  << std::endl;

	// initialize glut
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	//glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	//glEnable(GL_MULTISAMPLE_ARB);
	//glutInitDisplayMode(GLUT_RGBA | GLUT_MULTISAMPLE);

	// set window parameters
	glutInitWindowSize(params::window_width, params::window_height);
	glutInitWindowPosition(0, 0);

	if(params::game_mode) {
		glutGameModeString(params::mode_string);
		glutEnterGameMode();
	} else {
		glutCreateWindow("Logic Games");
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

	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_POLYGON_SMOOTH);

	//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_POINT_SMOOTH);

	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_LINE_SMOOTH);

	//glEnable(GL_MULTISAMPLE);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);

	//glEnable(GL_LINE_STIPPLE);

	//screen.switch_to(200, 150);
	//screen.switch_to(100, 100);

	// drawing
	glutDisplayFunc(graphics::display);
	glutReshapeFunc(graphics::reshape);

	glutIdleFunc(graphics::idle);
	glutTimerFunc(graphics::sleep, graphics::redisplay, 0);

	//glutTimerFunc(graphics::sleep, graphics::animate, 0);
	//glutTimerFunc(params::titres_timeout * 1000, engine::menu_autoload, 0);

	// commands
	glutKeyboardFunc(controls::keyboard);
	glutSpecialFunc(controls::special);
	glutMouseFunc(controls::mouse);

	lib::stage("LOADING");

	screen.initialize();

	application.set(LOADING_MODE);

	// loading fonts

	// loading interface
	interface.load();

	application.set(FOREWORD_MODE);

	lib::stage(
		"STARTING GAME\n"
		"press `p` to pause game\n"
		"press `ctrl-q` to quit immediatly\n"
	);

	// main loop
	glutMainLoop();

	return EXIT_SUCCESS;
}
