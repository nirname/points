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
#include <cmath>

Timer::Timer() {
	int length = 8;
	width = length * (font.width + 1) + 1;
	height = round(width / options::aspect_ratio.aspect());
}

Timer::~Timer() {
}

//#include <stdio.h>      /* printf */

#include <iomanip>

void Timer::display() {

	time(&timer); // get current time; same as: timer = time(NULL)
	timeinfo = localtime(&timer);

	glPushMatrix();
	glTranslatef(1, (height - font.height) / 2.0, 0);

	std::stringstream stream;
	stream
		<< std::setw(2) << std::setfill('0') << timeinfo->tm_hour << ':'
		<< std::setw(2) << std::setfill('0') << timeinfo->tm_min << ':'
		<< std::setw(2) << std::setfill('0') << timeinfo->tm_sec;
		//<< std::ends;

	stream.str();

	draw_text(stream.str());

	/* time example */

	/*time_t timer;
	struct tm y2k;
	double seconds;

	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time(&timer); // get current time; same as: timer = time(NULL)
	*/

/*
time_t now;
struct tm *current;
now = time(0);
current = localtime(&now);
cout << "hour: " << current->tm_hour << endl;
cout << "mins: " << current->tm_min << endl;
cout << "sec: " << current->tm_sec << endl;

struct timeval detail_time;
gettimeofday(&detail_time,NULL);
cout << "milli: " << detail_time.tv_usec/1000 << endl;
*/

	//seconds = difftime(timer, mktime(&y2k));
	//printf ("%.f seconds since January 1, 2000 in the current timezone", seconds);

	glPopMatrix();
}
