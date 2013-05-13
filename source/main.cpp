#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <math.h>

#if defined(_WIN32) && defined(__GNUC__)
	#include <gl/freeglut.h>
#elif defined(__linux__) && defined(__GNUC__)
	#include <GL/freeglut.h>
#endif

float offset_x = 0, offset_y = 0;
float scale = 1;
float f_length = 10.0, f_width = 10.0;

#include "global.h"

//logic::Game current_game;

int main(int argc, char * argv[])
{
	//engine::Screen screen(10, 10);

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
		glutCreateWindow("Square");
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
	glOrtho(0.0, f_width, 0.0, f_length, -1.0, 1.0);
	//glOrtho(0.0, screen.size.width, 0.0, screen.size.height, -1.0, 1.0);

	// drawing
	glutDisplayFunc(picture::display);
	glutReshapeFunc(picture::reshape);

	glutIdleFunc(picture::idle);
	glutTimerFunc(50, picture::redisplay, 0);

	// commands
	glutKeyboardFunc(controls::keyboard);
	glutSpecialFunc(controls::special);
	glutMouseFunc(controls::mouse);

	// main loop
	glutMainLoop();

	//system("PAUSE");

	return EXIT_SUCCESS;
}
