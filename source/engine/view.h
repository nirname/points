#pragma once

namespace engine {

	const Point FORWARD_DIRECTION(1, 1);
	const Point BACKWARD_DIRECTION(-1, -1);

	// Displays part of specified field
	// at specified position at screen
	//
	struct View {

		Field * field;   // field represented by it's view
		Size size;       // view size; by default it is the same as field size is
		Point offset;    // field offset
		Point direction; // offset direction
		Point position;  // position at screen

		graphics::ColorPointer background_color, cells_color, grid_color, border_color;

		View() {
			field = NULL;
			direction = BACKWARD_DIRECTION;
			background_color = NULL;
			cells_color      = NULL;
			grid_color       = NULL;
			border_color     = NULL;
		}

		void adjust_size();

		View(Field * _field) {
			field = _field;
			adjust_size();
			direction = BACKWARD_DIRECTION;
		}

		Bound bound() {
			return Bound(Point(size.width, size.height) - Point(1, 1));
		}

		Bound border() {
			return Bound(Point(size.width, size.height));
		}

		void display();

		//void draw_optional();

		void draw_background(const Bound &);
		void draw_cells(const Bound &);
		void draw_grid(const Bound &);
		void draw_border();

		void draw_objects(const Bound &);

		void print(std::ostream & _ostream) const;

	}; // View

	void View::adjust_size() {
		size = field->size;
	}

	void View::print(std::ostream & _ostream) const {
		_ostream << "View#" << this << " ("
			<< "field: " << field
		<< ")";
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

			// positioning
			glPushMatrix();
				glTranslatef(position.column, position.row, 0);
				draw_background(view_bound);
				draw_cells(display_bound);
				glPushMatrix();
					glTranslatef(shift.column, shift.row, 0);
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
				graphics::grid(_bound);
			glPopAttrib();
		}
	}

	void View::draw_border() {
		if(border_color != NULL) {
			glPushAttrib(GL_CURRENT_BIT);
				border_color->use();
				graphics::border(size);
			glPopAttrib();
		}
	}

	void View::draw_cells(const Bound & bound) {
		if(cells_color != NULL) {
			glPushAttrib(GL_CURRENT_BIT);
				cells_color->use();
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
							graphics::square();
						glPopMatrix();
					}
				}
			glPopAttrib();
		}
	}

	void View::draw_background(const Bound & bound) {
		glPushAttrib(GL_CURRENT_BIT);
			if(background_color != NULL) {
				background_color->use();
				glRectf(0, 0, size.width, size.height);
			}/* else {
				glColor3ub(BLACK);
			}*/
		glPopAttrib();
	}

	void View::draw_objects(const Bound & real_bound) {
		// { drawing points
		/*std::cout << "View" << std::endl;
		std::cout << "----------" << std::endl;
		std::cout << "Position: "      << position << std::endl;
		std::cout << "Shift: "         << shift << std::endl;
		std::cout << "Real bound: "    << real_bound << std::endl;
		std::cout << "Display bound: " << display_bound << std::endl;
		/**/
		//std::cout << "Objects" << std::endl;
		//std::cout << "----------" << std::endl;
		//std::cout << shift << std::endl;
		/*for(PointsInformation::iterator i = field->data.points.begin(); i != field->data.points.end(); ++i) {
			std::cout << *i->second << std::endl;
		}*/
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
				if(field->data.points.find(placement) != field->data.points.end()){
					//std::cout << placement << std::endl;
					field->data.points[placement]->display(placement);
				}
			}
		}
		// drawing points }

	}

	std::ostream & operator << (std::ostream & _ostream, const View & _view) {
		_view.print(_ostream);
		return _ostream;
	}

} // namespace engine
