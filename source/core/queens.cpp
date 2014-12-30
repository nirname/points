#include "queens.hpp"
#include "drawing.hpp"
#include "shape.hpp"
#include <iostream>
#include "color.hpp"

Queens::Queens() {
	field_size = 8;
	size = Size(field_size + 2, field_size + 2);
	queens = new int[field_size];
	for(int i = 0; i < field_size; i ++) {
		queens[i] = -1;
	}

	//std::cout << "Queens:" << std::endl;
	//std::cout << "  " << shape.base << std::endl;
	/*for(int column = 0; column < field_size; column++) {
		for(int row = 0; row < field_size; row ++) {
			queens[column] += 1;
		}
	}*/
	put_a_queen(0, 0);

}

Queens::~Queens() {
	delete [] queens;
}

bool Queens::can_put_a_queen(int column, int row) {
	for(int i = 0; i < column; i++) {
		if(
			queens[i] == row ||
			queens[i] + (column - i) == row ||
			queens[i] - (column - i) == row
		) {
			return false;
		}
	}
	return true;
}

inline bool Queens::queen_in_field(int column, int row) {
	return (
		((-1 < column) && (column < field_size)) &&
		((-1 < row) && (row < field_size))
	);
}

bool Queens::put_a_queen(int column, int row) {
	std::cout << "[";
	for(int i = 0; i < field_size - 1; i++) {
		std::cout << queens[i] << ", ";
	}
	std::cout << queens[field_size - 1] << "]";
	std::cout
		<< " # (" << column << ", " << row << ")"
		<< " / " << queen_in_field(column, row)
		<< " / " << can_put_a_queen(column, row)
		<< std::endl;

	if(!queen_in_field(column, row)) {
		return false;
	}
	queens[column] = -1;
	if(can_put_a_queen(column, row)) {
		queens[column] = row;
		if(column == field_size - 1) {
			return true; // bingo!
		} else {
			if(put_a_queen(column + 1, 0)) {
				return true;
			} else {
				return put_a_queen(column, row + 1);
			}
		}
	} else {
		return put_a_queen(column, row + 1);
	}

}

void Queens::display() {
	glPushMatrix();
		glTranslatef(1, 1, 0);
		for(int i = 0; i < field_size; i++) {
			for(int j = 0; j < field_size; j++) {
				glPushMatrix();
					glPushAttrib(GL_CURRENT_BIT);
						glTranslatef(i, j, 0);
						if((i + j) % 2 == 0) {
							glRectf(0, 0, 1, 1);
							Color(WHITE).use();
						}
						if(queens[i] == j) {
							shape.display();
						}
					glPopAttrib();
				glPopMatrix();
			}
		}
	glPopMatrix();
}
