#pragma once

namespace test {

	using namespace engine;

	typedef std::set<Point> ObjectPoints;

	/// Contains objects and points for the field
	//
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

		inline bool add(Object *, const Point & = Point(0, 0));
		bool add(Object *, const ObjectPoints &, const Point & = Point(0, 0));

		void remove(Point);
		void remove(Object *);

		void clear(); // Clears all

		ObjectPoints * get(Object *); // Gets all object's points
		Object *       get(Point); // Gets an object by point

		// Aliases for `get`
		ObjectPoints * operator [] (Object *);
		Object *       operator [] (Point);

		void print(std::ostream &) const; // Puts all information to stream

	};


	Data::Data() {}

	Data::~Data() {
		clear();
	}

	/// Check if data contains an object
	//
	bool Data::contains(Object * _object) const {
		return objects.find(_object) != objects.end();
	}

	/// Check if data contains a point
	//
	bool Data::contains(Point _point) const {
		return points.find(_point) != points.end();
	}

	/// Adds object by it's mask to specified position
	//
	inline bool Data::add(Object * _object, const Point & _position) {
		return add(_object, _object->mask, _position);
	}

	/// Adds an object if necessary
	/// Adds points to object
	/// Translate points to specified position
	//
	bool Data::add(Object * _object, const ObjectPoints & _points, const Point & _position) {
		// Calculate new points' values and check them
		ObjectPoints points_buffer;
		for ( ObjectPoints::iterator
			i = _points.begin();
			i != _points.end();
			i ++ )
		{
			Point _point = *i + _position;
			if(!contains(_point)) {
				points_buffer.insert(_point);
			} else {
				points_buffer.clear();
				return false;
			}
		}
		// Add new object;
		if(!contains(_object)) {
			objects[_object] = ObjectPoints();
		}
		// Copy points to object points and data points
		ObjectPoints & object_points = objects[_object];
		for ( ObjectPoints::iterator
			i = points_buffer.begin();
			i != points_buffer.end();
			i++ )
		{
			object_points.insert(*i);
			points[*i] = _object;
		}
		return true;
	}

	/// Removes only one point from an object
	/// If the object contans no more points it will be removed too
	//
	void Data::remove(Point _point) {
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

	/// Removes whole ojbect with its points
	/// 'points' also will be cleared
	//
	void Data::remove(Object * _object) {
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

	/// Erases all object and points
	//
	void Data::clear() {
		objects.clear();
		points.clear();
	}

	/// Gets all object points
	//
	ObjectPoints * Data::get(Object * _object) {
		return (contains(_object))? &objects[_object] : NULL;
	}

	/// Gets an object by point
	//
	Object * Data::get(Point _point) {
		return (contains(_point))? points[_point] : NULL;
	}

	/// Alias for getting object
	//
	ObjectPoints * Data::operator [] (Object * _object) {
		get(_object);
	};

	/// Alias for getting points
	//
	Object * Data::operator [] (Point _point) {
		get(_point);
	}

	/// Prints this to stream
	//
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

	/// Alias for print
	//
	std::ostream & operator << (std::ostream & _ostream, const Data & _data) {
		_data.print(_ostream);
		return _ostream;
	}

}
