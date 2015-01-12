#include "options.hpp"
#include "variables.hpp"
#include "initializers.hpp"

#include "user_interface.hpp"

#include "opengl.hpp"

#include <iostream>

int main(int argc, char * argv[]) {

	/*int a = 5, b = 7;
	std::cout << "a - b " << a - b << std::endl;
	return 0;*/

	/*Color c = Color(287.529, 1.0, 1.0);
	std::cout << "hsv: " << c.hue << " " << c.saturation << " " << c.value << std::endl;
	std::cout << "rgb: " << c.red << " " << c.green << " " << c.blue << std::endl;
	return 0;*/

	std::cout << "\nLOGIC GAMES\n" << std::endl;
	std::cout
		<< "# Arcades, Puzzles & Classical games" << std::endl
		<< "# Where everything is made of bricks" << std::endl
		<< "# Inside one pretty pack" << std::endl;

	std::cout << "\nINITIALIZING\n" << std::endl;
	options::load();
	//variables::initialize(argc, argv);
	graphics::initialize(argc, argv);
	audio::initialize(argc, argv);
	std::cout << "\nInitialising is done" << std::endl;

	//return 0;

	std::cout << "\nLOADING\n" << std::endl;
	default_shape.load(options::shape_options);
	font.load(options::fonts_directory, options::font_name);
	interface.load(load_interface);
	std::cout << "\nLoading is done" << std::endl;

	std::cout << "\nWELCOME\n" << std::endl;
	std::cout
		<< "# check controls.yaml to see all the keys" << std::endl
		<< "# check settings.yaml to persanalize game" << std::endl
		<< "#" << std::endl
		<< "# press `ctrl-q` to quit immediatly\n" << std::endl;

	application.start();

	glutMainLoop();

	return 0;

}
