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
	std::cout << "main default 1st: " << (intptr_t)default_shape << std::endl;
	options::load();
	std::cout << "main default 2nd: " << (intptr_t)default_shape << std::endl;
	//variables::initialize(argc, argv);
	graphics::initialize(argc, argv);
	audio::initialize(argc, argv);
	std::cout << "Initializing: ok" << std::endl;

	std::cout << "\nLOADING\n" << std::endl;
	interface.load(); // TODO: loading fonts here
	std::cout << "Loading: ok" << std::endl;

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
