#include "queens.hpp"

#include <iostream>

#include "drawing.hpp"
#include "color.hpp"
#include "library.hpp"

Queens::Queens() {
	//field_size = rand() % 4 + 5; // from 4 to 8
	field_size = 8;
	size = Size(field_size + 2, field_size + 2);
	queens = new int[field_size];
	for(int i = 0; i < field_size; i++) {
		queens[i] = -1;
	}
	last_update = 0;

	put_a_queen(0, 0);
	current_solution = solutions.begin();

	/*for(Solutions::iterator i = solutions.begin(); i != solutions.end(); i++) {
		for (int j = 0; j < field_size; j += 1) {
			std::cout << (*i)[j];
		}
		std::cout << std::endl;
	}*/
	std::cout << "solutions: " << solutions.size() << std::endl;
}

Queens::~Queens() {
	delete [] queens;
	for(Solutions::iterator i = solutions.begin(); i != solutions.end(); i++) {
		delete [] (*i);
	}
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

void Queens::print_queens(int column, int row) {
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
}

#include <cstring>

void Queens::save_solution() {
	int * solution = new int[field_size];
	std::memcpy(solution, queens, field_size * sizeof(int));
	/*for(int i = 0; i < field_size; i++) {
		solution[i] = queens[i];
	}*/
	solutions.push_back(solution);
}

void Queens::put_a_queen(int column, int row) {
	if(queen_in_field(column, row)) {
		queens[column] = -1;
		if(can_put_a_queen(column, row)) {
			queens[column] = row;
			//print_queens(column, row);
			if(column == field_size - 1) {
				save_solution();
				return; // bingo!
			} else {
				put_a_queen(column + 1, 0);
			}
		} else {
			//print_queens(column, row);
		}
		put_a_queen(column, row + 1);
	}
}

void Queens::next_solution() {
	current_solution++;
	if(current_solution == solutions.end()) {
		current_solution = solutions.begin();
	}
	last_update = glutGet(GLUT_ELAPSED_TIME);
}

void Queens::draw_letter(int x, int y, char letter) {
	glPushMatrix();
		glTranslatef(x, y, 0);
		glScalef(1.0 / 7, 1.0 / 7, 0);
		glTranslatef(1, 1, 0);
		draw_text(to_string(letter));
	glPopMatrix();
}

void Queens::display() {

	if(solutions.empty()) {
		return;
	}

	if(glutGet(GLUT_ELAPSED_TIME) - last_update > 2000 || last_update == 0) {
		next_solution();
	}

	glPushMatrix();
		glTranslatef(1, 1, 0);
		for(int i = 0; i < field_size; i++) {
			draw_letter(-1,         i, (char)((int)'0' + (i + 1) % 10));
			draw_letter(field_size, i, (char)((int)'0' + (i + 1) % 10));
			draw_letter(i,         -1, (char)((int)'a' + i));
			draw_letter(i, field_size, (char)((int)'a' + i));
			for(int j = 0; j < field_size; j++) {
				glPushMatrix();
					glPushAttrib(GL_CURRENT_BIT);
						glTranslatef(i, j, 0);
						if((i + j) % 2 == 0) {
							glRectf(0, 0, 1, 1);
							Color(WHITE).use();
						}
						if((*current_solution)[i] == j) {
							shape.display();
						}
					glPopAttrib();
				glPopMatrix();
			}
		}
		glBegin(GL_LINE_LOOP);
			glVertex2f(0, 0);
			glVertex2f(field_size, 0);
			glVertex2f(field_size, field_size);
			glVertex2f(0, field_size);
		glEnd();
	glPopMatrix();
}
