#include "animation.hpp"

#include "opengl.hpp"

Animation::Animation(ANIMATION_KIND _kind, ANIMATION_DIRECTION _direction):
	kind(_kind), direction(_direction)
{
	initialize();
}

void Animation::initialize() {
	state = READY;
	progress = (direction == FORWARD_ANIMATION)? 0 : 1;
}

void Animation::start() {
	if(state == READY || state == PAUSED) state = WORKING;
}

void Animation::stop() {
	if(state == WORKING) state = PAUSED;
}

void Animation::apply() {
	glTranslatef(0.5, 0.5, 0);
	/*switch(type) {
		case NO_ANIMATION: break;
		case FADE_ANIMATION: break;
		case SCALE_ANIMATION: glScalef(progress, progress, 0); break;
		case SLIDE_ANIMATION: break;
	}*/
	glTranslatef(-0.5, -0.5, 0);
}

void Animation::perform() {
/*		if(state == WORKING) {
		progress += (float)direction * 0.2;
		if(progress <= 0 || progress >= 1) {
			switch(continuation) {
				case SINGLE_ANIMATION: {
					state = FINISHED;
					do_after();
					if(auto_repair) repair();
					break;
				}
				case REPEAT_ANIMATION: progress = (direction == INCREASE)? 0 : 1; break;
				case REVERSE_ANIMATION: direction = (direction == INCREASE)? DECREASE : INCREASE; break;
			}
		}*/
		/*if(progress <= 0) {
			direction = 1;
		}*/
}
