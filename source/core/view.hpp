#pragma once

#include <cstddef>

#include "opengl.hpp"
#include "drawing.hpp"

#include "field.hpp"
#include "size.hpp"
#include "point.hpp"
#include "bound.hpp"
#include "color.hpp"

#include "options.hpp"

const Point FORWARD_DIRECTION(1, 1);
const Point BACKWARD_DIRECTION(-1, -1);

/// Displays part of specified field
/// at specified position at screen
//
struct View {

	Field * field;   // field represented by it's view
	Size size;       // view size; by default it is the same as field size is
	Point offset;    // field offset
	Point direction; // offset direction
	Point position;  // position at screen

	Color
		* background_color,
		* field_color,
		* cells_color,
		* grid_color,
		* border_color;

	View();
	View(Field * _field);

	void initialize();
	void adjust_size();

	Bound bound();
	Bound border();

	void display();

	void draw_background(const Bound &);
	void draw_cells(const Bound &);
	void draw_field(const Bound &);
	void draw_grid(const Bound &);
	void draw_border();

	void draw_objects(const Bound &);

};

View::View() {
	initialize();
}

View::View(Field * _field) {
	initialize();
	field = _field;
	adjust_size();
}

void View::initialize() {
	field = NULL;
	direction = BACKWARD_DIRECTION;
	background_color = NULL;
	field_color      = NULL;
	cells_color      = NULL;
	grid_color       = NULL;
	border_color     = NULL;
}

void View::adjust_size() {
	size = field->size;
}

Bound View::bound() {
	return Bound(Point(size.width, size.height) - Point(1, 1));
}

Bound View::border() {
	return Bound(Point(size.width, size.height));
}

void View::display()
{
	if(field != NULL) {
		Point shift = offset * direction;

		Bound view_bound = this->bound();
		Bound field_bound = field->bound() + shift;
		Bound display_bound = view_bound & field_bound;
		Bound real_bound = display_bound - shift;
		display_bound.final += Point(1, 1);

		// Positioning
		glPushMatrix();
			glTranslatef(position.column, position.row, 0);
			draw_background(view_bound);
			draw_field(display_bound);
			glPushMatrix();
				glTranslatef(shift.column, shift.row, 0);
				draw_cells(real_bound);
				draw_objects(real_bound);
			glPopMatrix();
			draw_grid(display_bound);
			draw_border();
		glPopMatrix();

	}
}

void View::draw_grid(const Bound & _bound) {
	if(grid_color != NULL) {
		glPushAttrib(GL_CURRENT_BIT);
			grid_color->use();
			//grid(_bound);
		glPopAttrib();
	}
}

void View::draw_border() {
	if(border_color != NULL) {
		glPushAttrib(GL_CURRENT_BIT);
			border_color->use();
			//graphics::border(size);
		glPopAttrib();
	}
}

void View::draw_field(const Bound & bound) {
	if(field_color != NULL) {
		glPushAttrib(GL_CURRENT_BIT);
			field_color->use();
			for (int row = bound.initial.row;
				row < bound.final.row;
				row++)
			{
				for (int column = bound.initial.column;
					column < bound.final.column;
					column++)
				{
					glPushMatrix();
						glTranslatef(column, row, 0);
						//graphics::default_shape();
					glPopMatrix();
				}
			}
		glPopAttrib();
	}
}

void View::draw_cells(const Bound & _bound) {
	if(cells_color != NULL) {
		glPushAttrib(GL_CURRENT_BIT);
			cells_color->use();
			for (int row = _bound.initial.row;
				row <= _bound.final.row;
				row++)
			{
				for (int column = _bound.initial.column;
					column <= _bound.final.column;
					column++)
				{
					Point cell(column, row);
					/*if(field->cells.find(cell) != field->cells.end()){
						glPushMatrix();
							glTranslatef(column, row, 0);
							graphics::default_shape();
						glPopMatrix();
					}*/
				}
			}
		glPopAttrib();
	}
}

void View::draw_background(const Bound & bound) {
	if(background_color != NULL) {
		glPushAttrib(GL_CURRENT_BIT);
			background_color->use();
			float outline = options::padding;
			glRectf(0 - outline, 0 - outline, size.width + outline, size.height + outline);
		glPopAttrib();
	}
}

void View::draw_objects(const Bound & real_bound) {
	for (int row = real_bound.initial.row;
		row <= real_bound.final.row;
		row++)
	{
		for (int column = real_bound.initial.column;
			column <= real_bound.final.column;
			column++)
		{
			Point placement(column, row);
			// TODO: move this part to field itself, then to data
			/*if(field->data.points.find(placement) != field->data.points.end()){
				field->data.points[placement]->display(placement);
			}*/
		}
	}
}
