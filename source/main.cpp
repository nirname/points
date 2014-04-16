#include "global.h"
#include "tests/_data_test.h"

#include <AL/al.h>
#include <AL/alc.h>
//#include <AL/alut.h>

int main(int argc, char * argv[])
{

	ALCdevice *device;

	device = alcOpenDevice(NULL);
	if (!device) {}

	//data_test();

	lib::stage("POINTS");
	std::cout << "Independent Logic Games" << std::endl;
	std::cout << "Arcades, Puzzles & Classical games" << std::endl;

	lib::stage("INITIALIZING");

	options::load();
	graphics::initialize(argc, argv);
	screen.initialize();

	lib::stage("LOADING");

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
	/**/

	return EXIT_SUCCESS;
}
