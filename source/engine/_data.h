#pragma once

namespace test {

	using namespace engine;

	typedef std::set<Point> ObjectPoints;

	class Data {

	private:

		typedef std::map<Point, Object *> PointsInformation;
		typedef std::map<Object *, ObjectPoints> ObjectsInformation;

		PointsInformation points;
		ObjectsInformation objects;

	public:

		Data();
		~Data();

		bool contains(Object *) const;
		bool contains(Point) const;

		bool add(Object *, const ObjectPoints &, const Point & = Point(0, 0));

		bool add_point(Object *, Point);
		bool add_object(Object *, Point); // Adds object to position

		void remove_point(Point);     // Removes point, and object if necessary
		void remove_object(Object *); // Removes all object and it's points
		void clear();                 // Clears all

		ObjectPoints * get_points(Object *); // Gets all object's points
		Object *       get_object(Point); // Gets an object by point

		// Aliases for `get`
		ObjectPoints * operator [] (Object *);
		Object *       operator [] (Point);

		void print(std::ostream &) const; // Puts all information to stream

	};


	Data::Data() {}

	Data::~Data() {
		clear();
	}

	bool Data::contains(Object * _object) const {
		return objects.find(_object) != objects.end();
	}

	bool Data::contains(Point _point) const {
		return points.find(_point) != points.end();
	}

	bool Data::add(Object * _object, const ObjectPoints & _mask, const Point & _position) {
		//TODO: write code here
	}

	bool Data::add_point(Object * _object, Point _point) {
		if(!contains(_object) || contains(_point)) {
			return false;
		} else {
			objects[_object].insert(_point);
			points[_point] = _object;
		}
	}

	// Adds an object by it's mask to specified position
	//
	bool Data::add_object(Object * _object, Point _position) {
		if(contains(_object)) {
			return false;
		} else {
			ObjectPoints _points; // buffer
			for ( ObjectPoints::iterator
				i = _object->mask.begin();
				i != _object->mask.end();
				i ++ )
			{
				Point _point = *i + _position; // calculate new point
				if(!contains(_point)) {
					_points.insert(_point);
				} else {
					_points.clear();
					return false;
				}
			}
			objects[_object] = _points;
			for ( ObjectPoints::iterator
				i = _points.begin();
				i != _points.end();
				i++ )
			{
				points[*i] = _object;
			}
		}
	}

	// Removes only one point from an object
	// If the object contans no more points it will be removed too
	//
	void Data::remove_point(Point _point) {
		if(contains(_point)) {
			Object * _object = points[_point];
			points.erase(_point);
			ObjectPoints * object_points = &objects[_object];
			object_points->erase(_point);
			if(object_points->empty()) {
				objects.erase(_object);
			}
		}
	}

	// Removes whole ojbect with its points
	// 'points' also will be cleared
	//
	void Data::remove_object(Object * _object) {
		if(contains(_object)) {
			ObjectPoints & object_points = objects[_object];
			for( ObjectPoints::iterator
				i = object_points.begin();
				i != object_points.end();
				++i )
			{
				points.erase(*i);
			}
			objects.erase(_object);
		}
	}

	void Data::clear() {
		objects.clear();
		points.clear();
	}

	ObjectPoints * Data::get_points(Object * _object) {
		return (contains(_object))? &objects[_object] : NULL;
	}

	Object * Data::get_object(Point _point) {
		return (contains(_point))? points[_point] : NULL;
	}

	ObjectPoints * Data::operator [] (Object * _object) {
		get_points(_object);
	};

	Object * Data::operator [] (Point _point) {
		get_object(_point);
	}

	void Data::print(std::ostream & _ostream) const {
		_ostream << "Data " << this << ":" << std::endl;
		_ostream << "  Objects:" << std::endl;
		for ( ObjectsInformation::const_iterator
			i = objects.begin();
			i != objects.end();
			++i
		) {
			_ostream << "    " <<  *i->first << std::endl;
			for ( ObjectPoints::const_iterator
				j = i->second.begin();
				j != i->second.end();
				++j
			) {
				_ostream << "      " << *j << std::endl;
			}
		}
		_ostream << "  Points:" << std::endl;
		for ( PointsInformation::const_iterator
			i = points.begin();
			i != points.end();
			++i
		) {
			_ostream << "    " << i->first << ": " << *i->second << std::endl;
		}

	}

	std::ostream & operator << (std::ostream & _ostream, const Data & _data) {
		_data.print(_ostream);
		return _ostream;
	}

}
