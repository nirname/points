#pragma once

namespace graphics {

	void display();
	void reshape(int, int);
	void idle();

}

namespace graphics {

	void display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPushAttrib(GL_CURRENT_BIT);
			glColor3ub(WHITE);
			glRectf(0.0, 0.0, screen.width, screen.height);
		glPopAttrib();
		glColor3ub(BLACK);

		// grid at screen
		/*glPushAttrib(GL_CURRENT_BIT);
			glColor3ub(GRAY);
			grid(screen.bound());
			glColor3ub(BLACK);
			grid(screen.bound(), 6);
		glPopAttrib();*/

		switch(application.mode) {
			case MENU_MODE: {
				interface.display();
				break;
			}
			case GAMEPLAY_MODE: {
				game.display();
				break;
			}
			case SCREENSAVER_MODE: { 
				screensaver.display();
				break;
			}
			default: {
				write(lib::to_string(application.mode));
				break;
			}
		}

		glFlush();
		glutSwapBuffers();

	}

	void redisplay(int timer)
	{
		//if(!game.paused) {
			clock_t time = clock();
			glutPostRedisplay();
			//time = clock() - time;
			//std::cout << "time: " << clock() << ", rest: " << graphics::sleep - time << std::endl;
			glutTimerFunc(graphics::sleep, redisplay, 0);
		//}
		//glutPostRedisplay();
		//glutTimerFunc(graphics::sleep, redisplay, 0);
	}

	void reshape(int width, int length)
	{
		//glOrtho(0.0, screen.width, 0.0, screen.height, -1.0, 1.0);

		//glViewport(0,0,(GLsizei)width, (GLsizei)length);
		//float side = (width < length) ? width : length;
		//float margin = 50.0;
		//float padding = 10.0;

		/*float x_ort = width / screen.width;
		float y_ort = length / screen.height;
		float side = (x_ort < y_ort) ? x_ort : y_ort;
		
		glViewport(
			(GLint)((width - side * screen.width) / 2.0),
			(GLint)((length - side * screen.height) / 2.0),
			(GLsizei)(side * screen.width),
			(GLsizei)(side * screen.height)
		);*/
		
		int x_ort = width / screen.width;
		int y_ort = length / screen.height;
		options::ort = (x_ort < y_ort) ? x_ort : y_ort;
		
		options::window_width = options::ort * screen.width;
		options::window_height = options::ort * screen.height;

		glViewport(
			(GLint)((width - options::window_width) / 2),
			(GLint)((length - options::window_height) / 2),
			(GLsizei)(options::window_width),
			(GLsizei)(options::window_height)
		);

	} // reshape

	void idle() {
	} // idle


}
