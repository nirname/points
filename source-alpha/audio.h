#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#define NUM_BUFFERS 8
#define NUM_SOURCES 8

void audio() {

	/*std::cout << "AUDIO" << std::endl;

	// Init openAL
	alutInit(0, NULL);
	// Clear Error Code (so we can catch any new errors)
	alGetError();

	ALuint buffers[NUM_BUFFERS];

	// Create the buffers
	alGenBuffers(NUM_BUFFERS, buffers);
	ALenum error;

	if ((error = alGetError()) != AL_NO_ERROR)
	{
		printf("alGenBuffers : %d", error);
		return;
	}

	ALenum     format;
	ALsizei    size;
	ALsizei    freq;
	ALboolean  loop;
	ALvoid*    data;

	// make sure to call alutInitWithoutContext first
	buffers[0] = alutCreateBufferFromFile("../additional/sounds/switch.wav");
	if( alutGetError() != ALUT_ERROR_NO_ERROR )
	{
		// handle the error
		return;
	}

	alutLoadWAVFile((ALbyte *)"../additional/sounds/switch.wav", &format, &data, &size, &freq, &loop);
	if((error = alGetError()) != AL_NO_ERROR)
	{
		printf("alutLoadWAVFile switch.wav : %d", error);
		// Delete Buffers
		alDeleteBuffers(NUM_BUFFERS, buffers);
		return;
	}

	alBufferData(buffers[0],format,data,size,freq);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		printf("alBufferData buffer 0 : %d", error);
		// Delete buffers
		alDeleteBuffers(NUM_BUFFERS, buffers);
		return;
	}

	alutUnloadWAV(format,data,size,freq);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		printf("alutUnloadWAV : %d", error);
		// Delete buffers
		alDeleteBuffers(NUM_BUFFERS, buffers);
		return 0;
	}

	ALuint source[NUM_SOURCES];
	// Generate the sources
	alGenSources(NUM_SOURCES, source);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		printf("alGenSources : %d", error);
		return;
	}*/



}
