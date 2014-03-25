#include "global.h"
#include "initialize.h"

int main(int argc, char * argv[])
{

	std::cout << std::endl;
	std::cout << "Independent Logic Games" << std::endl;
	std::cout << "Arcades, Puzzles & Classical games" << std::endl;
	std::cout << std::endl;

	lib::stage("INITIALIZING");

	options::load();

	graphics::initialize(argc, argv);

	lib::stage("LOADING");

	screen.initialize();

	application.set(LOADING_MODE);
	// Loading fonts
	interface.load(); // Loading interface

	application.set(FOREWORD_MODE);

	lib::stage(
		"STARTING GAME\n"
		"press `ctrl-q` to quit immediatly\n"
	);

	// main loop
	glutMainLoop();

	return EXIT_SUCCESS;
}
