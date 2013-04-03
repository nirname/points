#include <cstdlib>
#include <iostream>
#include <stdio.h>

#if defined(_WIN32) && defined(__GNUC__)
	#include <gl/freeglut.h>
#elif defined(__linux__) && defined(__GNUC__)
	#include <GL/freeglut.h>
#endif

float offset_x = 0, offset_y = 0;
float scale = 1;
float f_length = 22.0, f_width = 35.0;

#include "global.h"

int main(int argc, char * argv[])
{
	// uploading params from file
	prm::upload_params();

	// initialize glut
	glutInit(&argc, argv);

	glutInitDisplayMode(prm::display_mode);

	// set window parameters
	glutInitWindowSize(prm::window_width, prm::window_height);
	glutInitWindowPosition(0, 0);

	if(prm::game_mode) {
		glutGameModeString(prm::mode_string);
		glutEnterGameMode();
	} else {
		glutCreateWindow("Square");
		if(prm::full_screen) {
			glutFullScreen();
		}
	}

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, f_width, 0.0, f_length, -1.0, 1.0);

	// drawing
	glutDisplayFunc(pic::display);
	glutReshapeFunc(pic::reshape);

	glutIdleFunc(pic::idle);
	glutTimerFunc(50, pic::redisplay, 0);

	// commands
	glutKeyboardFunc(ctr::keyboard);
	glutSpecialFunc(ctr::special);
	glutMouseFunc(ctr::mouse);

	// main loop
	glutMainLoop();

	//system("PAUSE");
	return EXIT_SUCCESS;
}
