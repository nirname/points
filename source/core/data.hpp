#pragma once

#include <map>

#include "point_set.hpp"
#include "object.hpp"

struct Data {

	typedef std::map<Point, Object *> Objects;
	typedef std::map<Object *, PointSet> PointSets;

	Objects objects;
	PointSets point_sets;

	Data();
	~Data();

	bool contain(Object * object);
	bool contain(Object * object, typename PointSets::iterator & point_sets_iterator);
	bool contain(const Point & point);
	bool contain(const Point & point, typename Objects::iterator & objects_iterator);

	void add(Object * object, const Point & position = Point(0, 0));
	void add(Object * object, const Point & point, const Point & position = Point(0, 0));
	void add(Object * object, const PointSet & point_set, const Point & position = Point(0, 0));

	void remove(Object * object);
	void remove(const Point & point);
	void remove(const PointSet & point_set);

	void clear();

	PointSet * get(Object * object);
	Object *   get(const Point & point);

	PointSet * operator [] (Object * object);
	Object *   operator [] (const Point & point);

};
