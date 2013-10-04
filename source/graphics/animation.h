#ifndef ANIMATION_H
#define ANIMATION_H 1

namespace graphics {

	enum ANIMATION_TYPE {
		NO_ANIMATION  = 0,
		FADE_ANIMATION  = 1,
		SCALE_ANIMATION = 2,
		SLIDE_ANIMATION = 4,
		RANDOM_ANIMATION
	};

	enum ANIMATION_DIRECTION {
		DECREASE = -1,
		//PERMANENT = 0,
		INCREASE = 1
	};

	enum ANIMATION_STATE {
		READY,
		WORKING,
		PAUSED,
		FINISHED
	};

	enum ANIMATION_CONTINUATION {
		SINGLE_ANIMATION,
		REPEAT_ANIMATION,
		REVERSE_ANIMATION
	};

	struct Animation {
		//int duration; // msec
		ANIMATION_TYPE type;
		ANIMATION_DIRECTION direction;
		ANIMATION_STATE state;
		ANIMATION_CONTINUATION continuation;
		bool auto_repair;
		float progress;

		void (*do_after)(void);

		void initialize_progress() {
			progress = (direction == INCREASE)? 0 : 1;
		}

		Animation(ANIMATION_TYPE _type, ANIMATION_DIRECTION _direction = INCREASE) :
			type(_type), direction(_direction), state(READY), auto_repair(true)
		{
			initialize_progress();
		}

		void start() {
			if(state == READY || state == PAUSED) state = WORKING;
		}
		void stop() {
			if(state == WORKING) state = PAUSED;
		}

		void apply() {
			glTranslatef(0.5, 0.5, 0);
			switch(type) {
				case NO_ANIMATION: break;
				case FADE_ANIMATION: break;
				case SCALE_ANIMATION: glScalef(progress, progress, 0); break;
				case SLIDE_ANIMATION: break;
			}
			glTranslatef(-0.5, -0.5, 0);
		}

		void next() {
			if(state == WORKING) {
				progress += (float)direction * 0.2;
				//std::cout << "progress: " << progress << std::endl;
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
				}
				/*if(progress <= 0) {
					direction = 1;
				}*/
			}
		};

		void repair() {
			state = READY;
			initialize_progress();
		}; //clear

		void print(std::ostream & _ostream) const {
			_ostream << "Animation#" << this;
		}

	};

	std::ostream & operator << (std::ostream & _ostream, const graphics::Animation & entity) {
		entity.print(_ostream);
		return _ostream;
	}

}
#endif
