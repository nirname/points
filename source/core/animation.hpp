#pragma once

enum ANIMATION_KIND {
	NO_ANIMATION  = 0x00,
	FADE_ANIMATION  = 0x01,
	SCALE_ANIMATION = 0x02,
	SLIDE_ANIMATION = 0x04,
	ROTATE_ANIMATION = 0x08,
	//SHAKE_ANIMATION = 0x10,?
	RANDOM_ANIMATION = 0xFF
};

enum ANIMATION_DIRECTION {
	BACKWARD_ANIMATION = -1,
	//PERMANENT_ANIMATION = 0, // paused
	FORWARD_ANIMATION = 1
};

enum ANIMATION_STATE {
	READY,
	WORKING,
	PAUSED,
	FINISHED
};

enum ANIMATION_MODE {
	SIMPLE_ANIMATION = 0,
	BIDIRECTIONAL_ANIMATION = 1,
	MULTIPLE_ANIMATION = 2,
	MULTIBLE_BIDIRECTIONAL_ANIMATION = 3
};

struct Animation {

	int duration; // msec
	float progress; // 0 to 1, TODO: convert to msec?

	ANIMATION_KIND kind;
	ANIMATION_DIRECTION direction;
	ANIMATION_MODE mode;

	ANIMATION_STATE state;

	Animation(ANIMATION_KIND _kind, ANIMATION_DIRECTION _direction = FORWARD_ANIMATION);

	void initialize();

	/// Start or continue
	void start();
	/// Stop or pause
	void stop();
	/// Do transformations
	void apply();
	/// Calculate values for each frame
	void perform();

};
