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

	Shape * cell_shape;

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

	static void display(View *);

};
