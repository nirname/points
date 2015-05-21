#pragma once

#include <map>

#include "point_list.hpp"
#include "object.hpp"
#include "bound.hpp"

struct Data {

	typedef std::map<Point, Object *> Objects;
	typedef std::map<Object *, PointSet> PointSets;

	typedef PointSets::iterator PointSetsIterator;
	typedef PointSets::const_iterator ConstPointSetsIterator;
	typedef Objects::iterator ObjectsIterator;
	typedef Objects::const_iterator ConstObjectsIterator;

	// Map of `point` => `object` pairs
	Objects objects;
	// Map of `object` => `point set` pairs
	PointSets point_sets;

	Data();
	~Data();

	// Check whether data contain an object
	bool contain(Object * object);
	// Check whether data contain an object
	bool contain(Object * object, PointSetsIterator & point_sets_iterator);
	// Check whether data contain point
	bool contain(const Point & point);
	// Check whether data contain point
	bool contain(const Point & point, ObjectsIterator & objects_iterator);

	void add(Object * object, const Point & position);
	void add(Object * object, const Point & _point, const Point & position);
	void add(Object * object, const PointSet & point_set, const Point & position);

	void remove(Object * object);
	void remove(const Point & point);
	void remove(const PointSet & point_set);

	void clear();

	// Move an object at specified distance
	void move(Object * object, Point distance, const Bound & bound);
	void rotate(Object * object, Point point);

	PointSet * get(Object * object);
	Object *   get(const Point & point);

	PointSet * operator [] (Object * object);
	Object *   operator [] (const Point & point);

};
