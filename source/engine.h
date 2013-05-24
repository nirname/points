#ifndef ENGINE_H
#define ENGINE_H 1

#include "engine/primitives.h"

// engine
namespace engine {

	/*struct Cell
	{
		graphics::Color * color;
		//graphics::Shape * shape;
		//Cell(graphics::Color _color, graphics::Shape * shape)
	};*/

	struct Object
	{
		static int count;
		int number;
		graphics::Shape * shape;
		graphics::Color * color;

		Object(graphics::Shape * _shape, graphics::Color * _color):
			shape(_shape), color(_color)
		{
			number = count++;
		}

		~Object() {
			//--count;
		}

		void place(Field *, Point _position);
		void move(Field *, Point _step);
		//void rotate(Field * _field) {}
		//void symmetric(Field * _field) {}
		//transformation();

		/*struct Descendant
		{
			Point offset;
			Object * object;
			~Descendant() {
				delete object;
			}
		};*/
		//std::list<Descendant> descendants;
		//std::list<Points> descendants;
		void display(const Point & _position = Point()) {
			glPushMatrix();
			glTranslatef(_position.column, _position.row, 0);
			if(color != NULL) color->use();
			if(shape != NULL) shape->display();
			glPopMatrix();
		}
	};

	std::ostream & operator << (std::ostream & _ostream, const Object & _object) {
		_ostream << "Object(" << _object.number << ")";
		return _ostream;
	}

	int Object::count = 0;

	// Link between object and field
	struct Placement
	{
		Object * object;
		Field * field;
		Placement(Object * _object, Field * _field):
			object(_object), field(_field)
		{}
		std::string hash();
	};

	bool operator < (Placement a, Placement b) {
		return a.hash() < b.hash();
	}

	//class Figure {};

	// Contains width and height expressed by count of horizontal and vertical squares
	struct Screen {
		float width, height, margin;
		Screen(float _width = 10.0, float _height = 10.0, float _margin = 0.0):
			width(_width), height(_height), margin(_margin)
		{}
	};

	struct Level {
		std::string name;
		bool load() {
			return false;
		}
	};

	// make this types splitted by dimensions
	enum CLOSURE_TYPE
	{
		NO_CLOSURE,
		VERTICAL_CLOSURE,
		HORIZONTAL_CLOSURE,
		FULL_CLOSURE
	};

	// make this types splitted by dimensions
	enum INFINITY_TYPE
	{
		FINITE,
		VERTICAL_INFINITY,
		HORIZONTAL_INFINITY,
		FULL_INFINITY
	};

	struct Field
	{
		static int count;
		int number;
		Size size;
		CLOSURE_TYPE closure;
		Field(int _width = 1, int _height = 1)
		{
			size = Size(_width, _height);
			number = count++;
		}
		~Field() {
			//--count;
		}
		INFINITY_TYPE infinity_type() {
			return INFINITY_TYPE(
				(size.height == 0 ? VERTICAL_INFINITY : FINITE) |
				(size.width == 0 ? HORIZONTAL_INFINITY : FINITE)
			);
		}
		Bound bound() {
			return Bound(Point(size.width, size.height) - Point(1, 1)); //shift
		}
	};
	int Field::count = 0;

	std::ostream & operator << (std::ostream & _ostream, const Field & _field) {
		_ostream << "Field(" << _field.number << ")";
		return _ostream;
	}

	const Point FORWARD_DIRECTION(1, 1);
	const Point BACKWARD_DIRECTION(-1, -1);

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

		View(Field * _field, Point _position = Point(0, 0), Point _offset = Point(0, 0))
		{
			field = _field;
			size = _field->size;
			position = _position;
			offset = _offset;
			direction = BACKWARD_DIRECTION;
		}

		Bound bound() {
			//bool with_borders = false
			//Point shift(1, 1);
			//if(with_borders) shift = Point(0, 0);
			return Bound(Point(size.width, size.height) - Point(1, 1)); //shift
		}

		void display();
		void draw_grid(const Bound &);
		void draw_border();
		void draw_objects(const Bound &);
	};

	// Describes current game
	struct Game {

		logic::GAME_KIND game_kind;
		//engine::Screen screen;

		FieldMap  fields;
		ViewMap   views;
		ColorMap  colors;
		ShapeMap  shapes;
		ObjectMap objects;

		// Use unordered hash instead
		PointMap points;

		Game(logic::GAME_KIND _game_kind):
			game_kind(_game_kind)
		{}

		~Game(){
			for(FieldMap::iterator i = fields.begin(); i != fields.end(); ++i) {
				delete i->second;
			}
			for(ViewMap::iterator i = views.begin(); i != views.end(); ++i) {
				delete i->second;
			}
			for(ColorMap::iterator i = colors.begin(); i != colors.end(); ++i) {
				delete i->second;
			}
			for(ShapeMap::iterator i = shapes.begin(); i != shapes.end(); ++i) {
				delete i->second;
			}
			for(ObjectMap::iterator i = objects.begin(); i != objects.end(); ++i) {
				delete i->second;
			}
			for(PointMap::iterator i = points.begin(); i != points.end(); ++i) {
				delete i->second;
			}
		}

		/*FieldPointer add_field(const char * _name, int _width = 1, int _height = 1) {
			std::string field_name(_name);
			FieldPointer field;
			if(fields[field_name] != NULL) {
				field = fields[field_name];
				std::cout << "Field \"" << _name << "\" already exists" << std::endl;
			} else {
				field = new engine::Field(_width, _height);
				fields[field_name] = field;
			}
			return field;
		}*/

	};

	std::string Placement::hash() {
		if (object == NULL || field == NULL) {
			return std::string();
		}
		else {
			return std::string(lib::to_string(object->number) + lib::to_string(field->number));
		}
	}

	void Object::move(Field * _field, Point _step) {
		Placement placement(this, _field);
		Point * position = game.points[placement];
		if(position != NULL && _field->bound().contains(*position + _step)) {
			*(position) += _step;
		}
	}

	void View::display()
	{
		Point shift = offset * direction;

		Bound view_bound = this->bound();
		Bound field_bound = field->bound() + shift;
		Bound display_bound(
			max(view_bound.initial, field_bound.initial),
			min(view_bound.final, field_bound.final)
		);
		Bound real_bound(display_bound);

		display_bound.final += Point(1, 1);
		real_bound -= shift;

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

	void View::draw_grid(const Bound & display_bound) {
		glLineWidth(2);
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
		glLineWidth(5);
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
		for(PointMap::iterator i = game.points.begin(); i != game.points.end(); ++i) {
			glPushMatrix();
				if(i->second != NULL && real_bound.contains(*(i->second))) {
					//std::cout << *(i->second) << std::endl;
					i->first.object->display(*(i->second));
					glTranslatef(i->second->column, i->second->row, 0);
					//graphics::square();
				}
			glPopMatrix();
		}
		//std::cout << std::endl;
		// drawing points }
	}

} // engine

#endif