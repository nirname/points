#include "initializers.hpp"
#include "opengl.hpp"

#include "controls.hpp"
#include "options.hpp"
#include "color.hpp"
#include "display.hpp"
#include "graphics.hpp"

namespace graphics {

	void initialize(int argc, char * argv[]) {

		glutInit(&argc, argv);

		if(options::multisample) {
			glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
			glEnable(GL_MULTISAMPLE_ARB);
		} else {
			glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
		}

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

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_ALPHA_TEST);

		// drawing
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);

		glutIdleFunc(idle);
		//glutTimerFunc(graphics::sleep, redisplay, 0);
		//glutTimerFunc((int)1000/options::max_fps, redisplay, 0);
		glutTimerFunc(50, redisplay, 0);

		//glutTimerFunc(options::menu_timeout * 1000, engine::screensaver_autoload, 0);
		//glutTimerFunc(graphics::sleep, graphics::animate, 0);

		// controls
		glutKeyboardFunc(keyboard);
		glutSpecialFunc(special);
		glutMouseFunc(mouse);
		//coordinates(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
	}

}

namespace audio {
	void initialize(int argc, char * argv[]) {}
}
