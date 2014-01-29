#pragma once

namespace test {

	using namespace engine;

	typedef std::set<Point> ObjectPoints; // TODO: use unordered_set

	class Data {
	//struct Data {

	private:

		typedef std::map<Point, Object *> PointsInformation;
		typedef std::map<Object *, ObjectPoints> ObjectsInformation;

		PointsInformation points;
		ObjectsInformation objects;

	public:

		Data() {}

		~Data() {
			clear();
		}

		bool contains(Object *) const;
		bool contains(Point) const;

		void add(Object *, Point); // Adds point and object
		//void add(Point, Object *); // Does the same as previous one

		void remove(Point); // Removes point, and object, if it's last point for it
		void remove(Object *); // Removes all object and it's points
		void clear(); // Clears all

		ObjectPoints * get(Object *); // Gets all object's points
		Object * get(Point); // Gets an object which specified point belongs to

		void print(); // Log all information

	};

	bool Data::contains(Object * _object) const {
		return objects.find(_object) != objects.end();
	}

	bool Data::contains(Point _point) const {
		return points.find(_point) != points.end();
	}

	void Data::add(Object * _object, Point _point) {
		if(contains(_point)) {
			// TODO: resolve conflicts here
		} else {
			points[_point] = _object;
			if(contains(_object)) {
				objects[_object].insert(_point);
			} else {
				// TODO: do it with pointer to avoid extra copying?
				ObjectPoints buffer;
				buffer.insert(_point);
				objects[_object] = buffer;
			}
		}
	}

	//void Data::add(Point _point, Object * _object) {
	//	add(_object, _point);
	//}

	void Data::remove(Point _point) {
	}

	void Data::remove(Object * _object) {
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

	void Data::print() {
	}

}
