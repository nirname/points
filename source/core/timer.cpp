#include "timer.hpp"

#include <cstdlib>
#include "drawing.hpp"

#include "variables.hpp"
#include "options.hpp"
#include <iomanip>

Timer::Timer() {
	time(&timer);
	timeinfo = localtime(&timer);
	hue = calculate_hue();
	color.set(hue, 1.0, 1.0);

	size.width = 8 * (font.width + 1) + 1;
	size.height = round(size.width / options::aspect_ratio.aspect());
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
		color.set(hue, color.saturation, color.value);
		hue = current_hue;
	}

	glPushMatrix();
		glTranslatef(1, (size.height - font.height) / 2.0, 0);

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
