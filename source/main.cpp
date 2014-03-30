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

	/*for(int i = 32; i < 127; i++) {
		printf("%c", (char)i);
	}
	std::cout << std::endl;
	
	std::cout << "int: " << sizeof(int) << std::endl;
	std::cout << "unsigned int: " << sizeof(unsigned int) << std::endl;
	std::cout << "long int: " << sizeof(long int) << std::endl;
	std::cout << "long unsigned int: " << sizeof(long unsigned int) << std::endl;
	std::cout << "char: " << sizeof(char) << std::endl;
	std::cout << "unsigned char: " << sizeof(unsigned char) << std::endl;*/

	application.set(LOADING_MODE);
	// TODO: loading fonts here
	interface.load();
	application.start();

	lib::stage(
		"STARTING\n"
		"press `ctrl-q` to quit immediatly"
	);

	// main loop
	glutMainLoop();

	return EXIT_SUCCESS;
}
