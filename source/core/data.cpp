#include "data.hpp"

Data::Data() {}

Data::~Data() {
	clear();
}

bool Data::contain(Object * object) {
	return point_sets.find(object) != point_sets.end();
}

bool Data::contain(Object * object, typename PointSets::iterator & point_sets_iterator) {
	point_sets_iterator = point_sets.find(object);
	return point_sets_iterator != point_sets.end();
}

bool Data::contain(const Point & point) {
	return objects.find(point) != objects.end();
}

bool Data::contain(const Point & point, typename Objects::iterator & objects_iterator) {
	objects_iterator = objects.find(point);
	return objects_iterator != objects.end();
}

void Data::add(Object * object, const Point & position) {
	add(object, object->kind->mask, position);
}

void Data::add(Object * object, const Point & _point, const Point & position) {
	Point point = _point + position;
	if(!contain(point)) {
		// Add point to object
		PointSets::iterator object_points;
		if(contain(object, object_points)) {
			object_points->second.insert(point);
		} else {
			Point points_array[] = { point };
			point_sets[object] = PointSet(points_array, points_array + 1);
		}
		// Add link from point to object
		objects[point] = object;
	}
}

void Data::add(Object * object, const PointSet & point_set, const Point & position) {
	PointSets::iterator point_sets_iterator;
	PointSet & object_points =
		contain(object, point_sets_iterator) ?
		point_sets_iterator->second :
		point_sets[object] = PointSet();
	for( PointSet::iterator
		point_set_iterator = point_set.begin();
		point_set_iterator != point_set.end();
		++point_set_iterator
	) {
		Point point = *point_set_iterator + position;
		if(!contain(point)) {
			object_points.insert(point);
			objects[point] = object;
		}
	}
	if(object_points.empty()) {
		point_sets.erase(object);
	}
}

/// Removes whole ojbect with its points
/// 'points' also will be cleared
//
void Data::remove(Object * object) {
	if(contain(object)) {
		PointSet & object_points = point_sets[object];
		for( PointSet::iterator
			i = object_points.begin();
			i != object_points.end();
			++i )
		{
			objects.erase(*i);
		}
		point_sets.erase(object);
	}
}

void Data::remove(const Point & point) {
	typename Objects::iterator objects_iterator;
	if(contain(point, objects_iterator)) {
		Object * object = objects_iterator->second;
		point_sets[object].erase(point);
		if(point_sets[object].empty()) {
			point_sets.erase(object);
		}
		objects.erase(point);
	}
}

void Data::remove(const PointSet & point_set) {
	for( PointSet::iterator
		point_set_iterator = point_set.begin();
		point_set_iterator != point_set.end();
		++point_set_iterator
	) {
		Point point = *point_set_iterator;
		typename Objects::iterator objects_iterator;
		if(contain(point, objects_iterator)) {
			Object * object = objects_iterator->second;
			point_sets[object].erase(point);
			if(point_sets[object].empty()) { // TODO
				point_sets.erase(object);
			}
			objects.erase(point);
		}
	}

	/*for( PointSets::iterator
		point_sets_iterator = point_sets.begin();
		point_sets_iterator != point_sets.end();
		++point_sets_iterator
	) {
		if(point_sets_iterator->second.empty()) {
			point_sets.erase(point_sets_iterator);
		}
	}*/

}

void Data::clear() {
	objects.clear();
	point_sets.clear();
}

PointSet * Data::get(Object * object) {
	typename PointSets::iterator point_sets_iterator = point_sets.end();
	return (contain(object, point_sets_iterator)) ? &point_sets_iterator->second : NULL;
}

Object * Data::get(const Point & point) {
	typename Objects::iterator objects_iterator = objects.end();
	return (contain(point, objects_iterator)) ? objects_iterator->second : NULL;
}

PointSet * Data::operator [] (Object * object) {
	return get(object);
};

Object * Data::operator [] (const Point & point) {
	return get(point);
}
