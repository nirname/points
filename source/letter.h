#pragma once

struct Letter {

	unsigned short int width, height, baseline;
	bool bitmap[8][8];

	Letter() {
	}

};

/*
	glPushAttrib(GL_CURRENT_BIT);
	glColor3ub(SOFT_BLUE);

	glPushMatrix();
	glTranslatef(10, 0, 0);
	const int h = 7, w = 5;
	const int z = 3;
	bool a[h][w] = {
		{1, 0, 0, 0, 1},
		{1, 1, 0, 1, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
	}; // M
	bool a[h][w] = {
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
	}; // A
	bool a[h][w] = {
		{1, 0, 0, 0, 1},
		{1, 1, 0, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 0, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
	}; // N
	//for(int y = h-1; y >= 0; y--) {
	for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			if(a[y][x] == 1) {
				//point(x, (h-y-1)); // original size
				point(x*z, (h-y-1)*z); // expanded
				//for(int sx = 0; sx < z; sx++) {
					//point(x*z + sx, (h-y-1)*z + sx); // diagonal
					//point(x*z + sx, (h-y-1)*z); // IBM style, horizontal striped
					//point(x*z, (h-y-1)*z + sx); // vertical striped
					//for(int sy = 0; sy < z; sy++) {
					//	point(x*z + sx, (h-y-1)*z + sy); // scaled
					}
				//}
			}
		}
	}
	//point(0, 0); point(0, 1); point(0, 2); point(0, 3); point(0, 4); point(0, 5); point(0, 6);
	//point(1, 5); point(2, 4); point(3, 5);
	//point(4, 0); point(4, 1); point(4, 2); point(4, 3); point(4, 4); point(4, 5); point(4, 6);
	glPopMatrix();
	glPopAttrib();

	//graphics::grid(engine::Point(screen.width, screen.height));
*/
