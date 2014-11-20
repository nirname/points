#include "screensaver.hpp"

#include "drawing.hpp"
#include "library.hpp"
#include "emitter.hpp"


SCREENSAVER_KIND & operator ++ (SCREENSAVER_KIND & screensaver_kind, int) {
	int i = static_cast<int>(screensaver_kind);
	screensaver_kind = static_cast<SCREENSAVER_KIND>((i == 0)? 1 : i << 1);
	return screensaver_kind;
}

void Screensaver::display() {
	//graphics::write(lib::to_string(kind));
	draw_text(to_string(kind));
	/*switch(kind) {
		case NO_SCREENSAVER:                   break;
		case LIFE_SCREENSAVER:                 break;
		case QUEENS_SCREENSAVER:               break;
		case GEOGRAPHIC_EARTH_MAP_SCREENSAVER: break;
		case DAY_NIGHT_EARTH_MAP_SCREENSAVER:  break;
		case POLITICAL_EARTH_MAP_SCREENSAVER:  break;
		case TURTLE_SCREENSAVER:               break;
		case EQUALIZER_SCREENSAVER:            break;
		case TIMER_SCREENSAVER:                break;
		case RANDOM_SCREENSAVER:               break;
	}*/
}

void Screensaver::skip() {}
