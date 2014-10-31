#include "options.hpp"
#include "variables.hpp"
#include "initializers.hpp"

#include "opengl.hpp"

#include <iostream>

int main(int argc, char * argv[]) {

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

	std::cout << "\nLOADING\n" << std::endl;
	default_shape.load(options::shape_name);
	font.load(options::fonts_directory, options::font_name);
	interface.load();
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
