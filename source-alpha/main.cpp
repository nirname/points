#include "global.h"
#include "tests/_data_test.h"


#include "audio.h"


int main(int argc, char * argv[])
{

	std::cout << "AUDIO" << std::endl;

	ALuint helloBuffer, helloSource;
	alutInit(&argc, argv);
	//alutCreateBufferHelloWorld();
	helloBuffer = alutCreateBufferFromFile("../additional/sounds/switch.wav");
	//helloBuffer = alutCreateBufferFromFile("../additional/sounds/korob.mp3");
	alGenSources(1, &helloSource);
	alSourcei(helloSource, AL_BUFFER, helloBuffer);
	alSourcePlay(helloSource);
	alutSleep(1);
	alutExit();

	//data_test();

	lib::stage("POINTS");
	std::cout << "Independent Logic Games" << std::endl;
	std::cout << "Arcades, Puzzles & Classical games" << std::endl;

	lib::stage("INITIALIZING");

	options::load();

	graphics::initialize(argc, argv);
	//audio::initialize(argc, argv);

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
