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

		void add(Object *, Point); // Adds point and object

		void remove(Point);    // Removes point, and object, if it's last point for it
		void remove(Object *); // Removes all object and it's points
		void clear();          // Clears all

		ObjectPoints * get(Object *); // Gets all object's points
		Object *       get(Point);    // Gets an object which specified point belongs to

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

	void Data::add(Object * _object, Point _point) {
		if(contains(_point)) {
			// TODO: resolve conflicts and interactions here
		} else {
			points[_point] = _object;
			if(contains(_object)) {
				objects[_object].insert(_point);
				// TODO: do something here _object->mask ?
			} else {
				ObjectPoints buffer;
				buffer.insert(_point);
				objects[_object] = buffer;
			}
		}
	}

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

	void Data::remove(Object * _object) {
		if(contains(_object)) {
			ObjectPoints * object_points = &objects[_object];
			for( ObjectPoints::iterator
				i = object_points->begin();
				i != object_points->end();
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

	ObjectPoints * Data::get(Object * _object) {
		return (contains(_object))? &objects[_object] : NULL;
	}

	Object * Data::get(Point _point) {
		return (contains(_point))? points[_point] : NULL;
	}

	ObjectPoints * Data::operator [] (Object * _object) {
		get(_object);
	};

	Object * Data::operator [] (Point _point) {
		get(_point);
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

	// TODO: make >> operator for YAML
	// TODO: make >> operator for binary files

	std::ostream & operator << (std::ostream & _ostream, const Data & _data) {
		_data.print(_ostream);
		return _ostream;
	}

}
