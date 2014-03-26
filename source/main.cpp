#include "global.h"
#include "initialize.h"

int main(int argc, char * argv[])
{

	lib::stage("POINTS");
	std::cout << "Independent Logic Games" << std::endl;
	std::cout << "Arcades, Puzzles & Classical games" << std::endl;

	lib::stage("INITIALIZING");

	options::load();
	graphics::initialize(argc, argv);
	screen.initialize();

	lib::stage("LOADING");

	application.set(LOADING_MODE);
	// Loading fonts
	interface.load(); // Loading interface

	application.set(FOREWORD_MODE);

	lib::stage(
		"STARTING\n"
		"press `ctrl-q` to quit immediatly"
	);

	// main loop
	glutMainLoop();

	return EXIT_SUCCESS;
}
