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

void Data::add(Object * object, const Point & position) {}
void Data::add(Object * object, const Point & point, const Point & position) {}
void Data::add(Object * object, const PointSet & point_set, const Point & position) {}

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
