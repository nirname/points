#ifndef ENGINE_H
#define ENGINE_H 1

// engine
namespace engine {

	struct Point
	{
		int row;
		int column;

		Point(const Point & x):
			column(x.column), row(x.row)
		{}

		Point(int _column = 0, int _row = 0):
			column(_column), row(_row)
		{}

		Point & operator += (Point x) {
			row    += x.row;
			column += x.column;
			return * this;
		}

		Point & operator -= (Point x) {
			row    -= x.row;
			column -= x.column;
			return * this;
		}

		bool operator < (const Point & x) const {
			return column < x.column && row < x.row;
		}

		bool operator <= (const Point & x) const {
			return column <= x.column && row <= x.row;
		}

	};

	std::ostream & operator << (std::ostream & _ostream, const Point & _point) {
		_ostream << "Point(" << _point.column << ", " << _point.row << ")";
	}

	Point operator + (Point a, Point b)
	{
		Point result(a);
		return result += b;
	}

	Point operator - (Point a, Point b)
	{
		Point result(a);
		return result -= b;
	}

	Point min(Point a, Point b)
	{
		return Point(
			std::min(a.column, b.column),
			std::min(a.row, b.row)
		);
	}

	Point max(Point a, Point b)
	{
		return Point(
			std::max(a.column, b.column),
			std::max(a.row, b.row)
		);
	}

	struct Size
	{
		int width;
		int height;
		Size(int _width = 1, int _height = 1):
			width(_width), height(_height)
		{}
	};

	struct Bound {
		Point initial, final;
		Bound(Point _initial, Point _final):
			initial(_initial), final(_final)
		{ /* do not normilize here*/ }
		Bound(const Bound & _bound):
			initial(_bound.initial), final(_bound.final)
		{}

		bool contains(Point x) {
			return initial <= x && x <= final;
		}

		Bound & operator +=(Point x) {
			initial += x;
			final   += x;
			return * this;
		}
		Bound & operator -=(Point x) {
			initial -= x;
			final   -= x;
			return * this;
		}
	};

	std::ostream & operator << (std::ostream & _ostream, const Bound & _bound) {
		_ostream << "Bound(" << _bound.initial << ", " << _bound.final << ")";
		return _ostream;
	}
	/*Bound operator + (Bound _bound, Point _point)
	{
		Bound result = _bound;
		return result += _point;
	}*/
	/*Bound operator - (Bound _bound, Point _point)
		/*Bound result = _bound;
		return result -= _point;
	}*/

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
			--count;
		}

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
		void display(Point _position = Point()) {
			glPushMatrix();
			glTranslatef(_position.column, _position.row, 0);
			color->use();
			shape->display();
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
			--count;
		}
		INFINITY_TYPE infinity_type() {
			return INFINITY_TYPE(
				(size.height == 0 ? VERTICAL_INFINITY : FINITE) |
				(size.width == 0 ? HORIZONTAL_INFINITY : FINITE)
			);
		}
	};
	int Field::count = 0;

	std::ostream & operator << (std::ostream & _ostream, const Field & _field) {
		_ostream << "Field(" << _field.number << ")";
		return _ostream;
	}

	// Contains width and height expressed by count of horizontal and vertical squares
	struct Screen {
		float width, height, margin;
		Screen(float _width = 10.0, float _height = 10.0, float _margin = 0.0):
			width(_width), height(_height), margin(_margin)
		{}
	};

	// Displays part of specified field
	// at specified position at screen
	struct View
	{
		Field * field;
		Size size; // view size; by default it is the same as field size is
		Point offset; // field offset
		//Screen * screen;
		Point position; // position at screen

		View(Field * _field, Point _position = Point(0, 0), Point _offset = Point(0, 0))
		{
			field = _field;
			size = _field->size;
			position = _position;
			offset = _offset;
		}

		void display();
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

	};

	std::string Placement::hash() {
		if (object == NULL || field == NULL) {
			return std::string();
		}
		else {
			return std::string(std::to_string(object->number) + std::to_string(field->number));
		}
	}

	void Object::move(Field * _field, Point _step) {
		Placement placement(this, _field);
		//if(game.points[placement] == NULL)
		//_game->points[Placement(this, _field)];
	}

	void View::display()
	{
		Bound view_bound(
			Point(0, 0),
			Point(size.width, size.height)
		);
		Bound field_bound(
			Point(0, 0),
			Point(field->size.width, field->size.height)
		);
		field_bound -= offset;
		Bound display_bound(
			max(view_bound.initial, field_bound.initial),
			min(view_bound.final, field_bound.final)
		);
		Bound real_bound(display_bound);
		real_bound += offset;
		/*Point v1(0, 0);
		Point v2(size.width, size.height);

		Point f1 = Point(0, 0) - offset;
		Point f2 = Point(field->size.width, field->size.height) - offset;

		Point bound1 = max(v1, f1);
		Point bound2 = min(v2, f2);*/

		glPushMatrix();
		glTranslatef(position.column, position.row, 0);
		// { drawing croped grid
		glLineWidth(2);
		glBegin(GL_LINES);
		/*if(bound1.row < bound2.row) {
			for(int x = bound1.column; x <= bound2.column; x++) {
				glVertex2f(x, bound1.row);
				glVertex2f(x, bound2.row);
			}
		}
		if(bound1.column < bound2.column) {
			for(int y = bound1.row; y <= bound2.row; y++) {
				glVertex2f(bound1.column, y);
				glVertex2f(bound2.column, y);
			}
		}*/
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
		// drawing croped grid }

		// { drawing border
		glLineWidth(5);
		glColor3ub(VIOLET);

		glBegin(GL_LINE_LOOP);
		glVertex2f(0         , 0          );
		glVertex2f(size.width, 0          );
		glVertex2f(size.width, size.height);
		glVertex2f(0         , size.height);
		glEnd();

		// drawing border }

		// { drawing points

		/*std::cout << "----------" << std::endl;
		std::cout << "Position: " << position << std::endl;
		std::cout << "Offset: " << offset << std::endl;
		std::cout << "Real bound: " << real_bound << std::endl;
		std::cout << "Display bound: " << display_bound << std::endl;*/
		// drawing points }

		for(PointMap::iterator i = game.points.begin(); i != game.points.end(); ++i) {
			if(i->second != NULL) {
				if( real_bound.contains(*(i->second)) ) {
					//std::cout << *(i->second) << std::endl;
					i->first.object->display(*(i->second) - offset);
				}
			}
		}

		glPopMatrix(); // move at initial position

	}



} // engine

#endif
