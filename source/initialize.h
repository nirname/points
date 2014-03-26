namespace graphics {

	void initialize(int argc, char * argv[]) {

		// Initializing glut
		glutInit(&argc, argv);

		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); // GLUT_MULTISAMPLE
		//glEnable(GL_MULTISAMPLE_ARB);

		// Setting window parameters
		glutInitWindowSize(options::window_width, options::window_height);
		glutInitWindowPosition(0, 0);

		if(options::game_mode) {
			glutGameModeString(options::mode_string);
			glutEnterGameMode();
		} else {
			glutCreateWindow("Logic Games");
			if(options::full_screen) {
				glutFullScreen();
			}
		}

		// creating game
		// testing inside display function

		/*glClearColor(
			options::clear_color.red,
			options::clear_color.green,
			options::clear_color.blue,
			0.5f
		);*/
		glClearColor(WHITE, 0.5f);
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

		// commands
		glutKeyboardFunc(controls::keyboard);
		glutSpecialFunc(controls::special);
		glutMouseFunc(controls::mouse);
	}

}
