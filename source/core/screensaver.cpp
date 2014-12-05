#include "screensaver.hpp"

#include "drawing.hpp"
#include "library.hpp"
#include "emitter.hpp"

SCREENSAVER_KIND & operator ++ (SCREENSAVER_KIND & screensaver_kind, int) {
	int i = static_cast<int>(screensaver_kind);
	screensaver_kind = static_cast<SCREENSAVER_KIND>((i == 0)? 1 : i << 1);
	return screensaver_kind;
}

BasicScreensaver::BasicScreensaver() {
	width = 12;
	height = 12;
}

BasicScreensaver::~BasicScreensaver() {}

void BasicScreensaver::display() {
	draw_text("Basic screensaver");
}

Screensaver::Screensaver() {
	basic_screensaver = NULL;
}

Screensaver::~Screensaver() {
	skip();
}

bool Screensaver::load(const SCREENSAVER_KIND & kind) {
	skip();
	if(kind == NO_SCREENSAVER) {
		return false;
	}
	//SCREENSAVER_KIND
	//int number = rand() % 8 + 1;
	SCREENSAVER_KIND choice = kind;
	switch(choice) {
		case LIFE_SCREENSAVER:                 break;
		case QUEENS_SCREENSAVER:               break;
		case GEOGRAPHIC_EARTH_MAP_SCREENSAVER: break;
		case DAY_NIGHT_EARTH_MAP_SCREENSAVER:  break;
		case POLITICAL_EARTH_MAP_SCREENSAVER:  break;
		case TURTLE_SCREENSAVER:               break;
		case EQUALIZER_SCREENSAVER:            break;
		case TIMER_SCREENSAVER: {
			basic_screensaver = new Timer();
			return true;
			break;
		}
		default: return false;
	}
	return false;
}

bool Screensaver::is_loaded() {
	return basic_screensaver != NULL;
}

void Screensaver::skip() {
	if(is_loaded()) {
		delete basic_screensaver;
		basic_screensaver = NULL;
	}
}

void Screensaver::display() {
	if(is_loaded()) {
		basic_screensaver->display();
	}
}

int Screensaver::width() {
	if(is_loaded()) {
		return basic_screensaver->width;
	} else {
		return 0;
	}
}

int Screensaver::height() {
	if(is_loaded()) {
		return basic_screensaver->height;
	} else {
		return 0;
	}
}

/*Queens::Queens() {
	size = 8; //std::rand() %
	width = height = size;
	field = new int[size];
}

Queens::~Queens() {
	delete [] field;
}

void Queens::display() {
	draw_text("QQQQ");
}*/

#include "variables.hpp"
#include "options.hpp"
#include <iomanip>

Timer::Timer() {
	time(&timer);
	timeinfo = localtime(&timer);
	hue = calculate_hue();
	color.set(hue, 1.0, 1.0);

	width = 8 * (font.width + 1) + 1;
	height = round(width / options::aspect_ratio.aspect());
}

Timer::~Timer() {
}

double Timer::calculate_hue() {
	return timeinfo->tm_min % 6 * 60 + timeinfo->tm_sec;
}

void Timer::display() {
	time(&timer);
	timeinfo = localtime(&timer);
	double current_hue = calculate_hue();
	if(current_hue != hue) {
		color.set(hue, 1.0, 1.0);
		hue = current_hue;
	}

	glPushMatrix();
		glTranslatef(1, (height - font.height) / 2.0, 0);

		std::stringstream stream;
		stream
			<< std::setw(2) << std::setfill('0') << timeinfo->tm_hour << ':'
			<< std::setw(2) << std::setfill('0') << timeinfo->tm_min << ':'
			<< std::setw(2) << std::setfill('0') << timeinfo->tm_sec;

		glPushAttrib(GL_CURRENT_BIT);
			color.use();
			draw_text(stream.str());
		glPopAttrib();

	glPopMatrix();
}
