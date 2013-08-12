#ifndef VIEW_H
#define VIEW_H 1

namespace engine {

	const Point FORWARD_DIRECTION(1, 1);
	const Point BACKWARD_DIRECTION(-1, -1);

	enum POSITION_TYPE {
		ORIGIN,
		CENTER
	};

	// Displays part of specified field
	// at specified position at screen
	struct View
	{
		Field * field;
		Size size; // view size; by default it is the same as field size is
		Point offset; // field offset
		Point direction; // offset direction
		// (!) use ORIGIN and CENTER
		//Screen * screen;
		Point position; // position at screen

		View() {
			direction = BACKWARD_DIRECTION;
		}

		View(Field * _field) {
			field = _field;
			size = _field->size;
			direction = BACKWARD_DIRECTION;
		}

		/*Point set_position(POSITION_TYPE x) {
			return position;
		}

		Point set_offset(POSITION_TYPE x) {
		}*/

		Bound bound() {
			return Bound(Point(size.width, size.height) - Point(1, 1));
		}

		Bound border() {
			return Bound(Point(size.width, size.height));
		}

		void display();
		void draw_grid(const Bound &);
		void draw_border();
		void draw_objects(const Bound &);
	};

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
				draw_grid(display_bound);
				draw_border();
				glPushMatrix();
					glTranslatef(shift.column, shift.row, 0);
					draw_objects(real_bound);
				glPopMatrix();
			glPopMatrix();

		}
	}

	void View::draw_grid(const Bound & display_bound) {
		//glLineWidth(2);
		glBegin(GL_LINES);
			if(display_bound.initial.row < display_bound.final.row) {
				for(int x = display_bound.initial.column; x <= display_bound.final.column; x++) {
					glVertex2f(x, display_bound.initial.row);
					glVertex2f(x, display_bound.final.row);
				}
			}
			if(display_bound.initial.column < display_bound.final.column) {
				for(int y = display_bound.initial.row; y <= display_bound.final.row; y++) {
					glVertex2f(display_bound.initial.column, y);
					glVertex2f(display_bound.final.column, y);
				}
			}
		glEnd();
	}

	void View::draw_border() {
		// { drawing border
		//glLineWidth(5);
		//glPushAttrib(GL_CURRENT_BIT);
		//glColor3ub(VIOLET);
		glBegin(GL_LINE_LOOP);
			glVertex2f(0         , 0          );
			glVertex2f(size.width, 0          );
			glVertex2f(size.width, size.height);
			glVertex2f(0         , size.height);
		glEnd();/**/
		//glPopAttrib(CL_CURRENT_BIT);
		// drawing border }
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
				if(field->data.points.find(placement) != field->data.points.end()){
					//std::cout << placement << std::endl;
					field->data.points[placement]->display(placement);
				}
			}
		}
		/*for(PointMap::iterator i = game.points.begin(); i != game.points.end(); ++i) {
			if(i->second != NULL && real_bound.contains(*(i->second))) {
				//std::cout << *(i->second) << std::endl;
				i->first.object->display(*(i->second));
				//glTranslatef(i->second->column, i->second->row, 0);
				//graphics::square();
			}
		}*/
		//std::cout << std::endl;
		// drawing points }
	}

}

#endif
