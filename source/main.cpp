#include "global.h"

engine::Screen screen(22.0, 22.0); // move screen to game?
engine::Game game(logic::SOKOBAN);

int main(int argc, char * argv[])
{
	// move this logic to Level class
	//game.add_field("Field", 10, 10);
	//game.add_view("View", "Field");
	//std::cout << (engine::Point(0, 0) < engine::Point(0, 1)) << std::endl;
	game.fields[std::string("Field")] = new engine::Field(10, 10);

	game.views[std::string("View")] = new engine::View(game.fields[std::string("Field")]);
	game.views[std::string("View")]->size     = engine::Size(12, 12);
	game.views[std::string("View")]->offset   = engine::Point(-1, -1);
	game.views[std::string("View")]->position = engine::Point(3, 3);

	//const char * shape_names [2] = ["a", "b"];
	//engine::Object aaa();
	//engine::Object bbb(aaa);

	/*game.colors[std::string("Violet")] = new graphics::Color(VIOLET);
	game.colors[std::string("Blue")] = new graphics::Color(BLUE);
	game.colors[std::string("Green")] = new graphics::Color(GREEN);
	game.shapes[std::string("Square")] = new graphics::Square();
	game.shapes[std::string("Circle")] = new graphics::Circle();
	game.shapes[std::string("David")] = new graphics::David();*/
	graphics::Shape * sokoban_shape =  new graphics::Star();
	game.shapes[std::string("SokobanShape")] = sokoban_shape;
	//game.shapes[std::string("Ring")] = new graphics::Ring();

	engine::Object * box;
	box = new engine::Object();
	box->kind = "Box";
	game.objects[std::string("Box1")] = box;
	box = new engine::Object();
	box->kind = "Box";
	game.objects[std::string("Box2")] = box;

	//game.objects[std::string("Box2")] = new engine::Object();
	/*game.objects[std::string("Box1")]->type = std::string("Box");
	game.objects[std::string("Box2")]->type = std::string("Box");*/

	engine::Object * sokoban = new engine::Object();
	sokoban->shape = sokoban_shape;
	sokoban->kind = "Sokoban";
	game.objects[std::string("Sokoban")] = sokoban;

	std::cout << game.fields[std::string("Field")]->data.add(game.objects[std::string("Sokoban")], engine::Point(1, 1)) << std::endl;

	std::cout << game.fields[std::string("Field")]->data.add(game.objects[std::string("Box1")], engine::Point(5, 5)) << std::endl;
	std::cout << game.fields[std::string("Field")]->data.add(game.objects[std::string("Box2")], engine::Point(6, 5)) << std::endl;


	game.interactions[engine::PairOfKinds(std::string("Sokoban"), std::string("Box"))] = engine::PUSH_INTERACTION;
	//game.points[ engine::Placement(game.objects[std::string("Sokoban")], game.fields[std::string("Field")]) ] = new engine::Point(1, 1);
	//game.points[ engine::Placement(game.objects[std::string("Box1")], game.fields[std::string("Field")]) ] = new engine::Point(2, 2);
	//game.points[ engine::Placement(game.objects[std::string("Box2")], game.fields[std::string("Field")]) ] = new engine::Point(3, 3);

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

	//glEnable(GL_LINE_SMOOTH);
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_POINT_SMOOTH);
	//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glShadeModel(GL_SMOOTH);    // Разрешить плавное сглаживание
	//glClearColor(0.0f, 0.0f, 0.0f, 0.5f);   // Черный фон
	//glClearDepth(1.0f);         // Настройка буфера глубины
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Сглаживание линий
	//glEnable(GL_BLEND);         // Разрешить смешивание
	//glEnable(GL_LINE_SMOOTH);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(BLACK, 0.0);

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

	// main loop
	glutMainLoop();

	//system("PAUSE");

	return EXIT_SUCCESS;
}
