#include "global.h"

engine::Screen screen(22.0, 22.0); // move screen to game?
engine::Game game(logic::SOKOBAN);

int main(int argc, char * argv[])
{
	// move this logic to Level class
	game.add_field("Field", 10, 10);
	//game.add_view("View", "Field");
	//game.fields[std::string("Field")] = new engine::Field(20, 20);
	game.views[std::string("View")] = new engine::View(game.fields[std::string("Field")]);
	game.views[std::string("View")]->size = engine::Size(12, 12);
	game.views[std::string("View")]->offset = engine::Point(-1, -1);
	game.views[std::string("View")]->position = engine::Point(3, 3);

	game.colors[std::string("Violet")] = new graphics::Color(VIOLET);
	game.colors[std::string("Blue")] = new graphics::Color(BLUE);
	game.colors[std::string("Green")] = new graphics::Color(GREEN);
	game.shapes[std::string("Square")] = new graphics::Square();

	game.objects[std::string("Box1")] = new engine::Object(
		game.shapes[std::string("Square")],
		game.colors[std::string("Green")]
	);
	game.objects[std::string("Box2")] = new engine::Object(
		game.shapes[std::string("Square")],
		game.colors[std::string("Blue")]
	);
	game.objects[std::string("Sokoban")] = new engine::Object(
		game.shapes[std::string("Square")],
		game.colors[std::string("Violet")]
	);

	game.points[ engine::Placement(game.objects[std::string("Box1")], game.fields[std::string("Field")]) ] = new engine::Point(3, 3);
	game.points[ engine::Placement(game.objects[std::string("Box2")], game.fields[std::string("Field")]) ] = new engine::Point(2, 2);
	game.points[ engine::Placement(game.objects[std::string("Sokoban")], game.fields[std::string("Field")]) ] = new engine::Point(1, 1);

	/*for(engine::PointMap::iterator i = game.points.begin(); i != game.points.end(); ++i) {
		std::cout << *(i->first.object) << " at " << *(i->first.field) << " : ";
		if(i->second != NULL) {
			std::cout << *(i->second) << std::endl;
		} else {
			std::cout << "no position" << std::endl;
		}
	}
	std::cout << std::ends;*/

	//std::count << (&(game.points[ engine::Placement(game.objects[std::string("Sokoban")], game.fields[std::string("Field")]) ]) == NULL);

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
