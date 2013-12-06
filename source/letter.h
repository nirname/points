#ifndef LETTER_H
#define LETTER_H 1

struct Letter {
	unsigned short int width, height, baseline;
	bool bitmap[8][8];

	Letter() {

	}

};

#endif
