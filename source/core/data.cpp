#include "data.hpp"
#include <iostream>
#include "emitters/point_emitter.hpp"
#include "interaction.hpp"

Data::Data() {}

Data::~Data() {
	clear();
}

/// Check whether point_sets contain an object
bool Data::contain(Object * object) {
	return point_sets.find(object) != point_sets.end();
}

/// Check whether point_sets contain an object
/// and fetch an iterator to <object, point_set> pair
bool Data::contain(Object * object, typename PointSets::iterator & point_sets_iterator) {
	point_sets_iterator = point_sets.find(object);
	return point_sets_iterator != point_sets.end();
}

/// Check whether objects contain a point
bool Data::contain(const Point & point) {
	return objects.find(point) != objects.end();
}

/// Check whether objects contain a point
/// and fetch an iterator to <point, object> pair
bool Data::contain(const Point & point, typename Objects::iterator & objects_iterator) {
	objects_iterator = objects.find(point);
	return objects_iterator != objects.end();
}

void Data::add(Object * object, const Point & position) {
	if(object->kind != NULL) {
		add(object, object->kind->mask, position);
	} else {
		add(object, Point(0, 0), position);
	}
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

/// Removes only one point from object
//
void Data::remove(const Point & point) {
	ObjectsIterator objects_iterator;
	if(contain(point, objects_iterator)) {
		Object * object = objects_iterator->second;
		point_sets[object].erase(point);
		if(point_sets[object].empty()) {
			point_sets.erase(object);
		}
		objects.erase(point);
	}
}

/// Removes collection of points from data
//
void Data::remove(const PointSet & point_set) {
	for( PointSet::iterator
		point_set_iterator = point_set.begin();
		point_set_iterator != point_set.end();
		++point_set_iterator
	) {
		Point point = *point_set_iterator;
		ObjectsIterator objects_iterator;
		if(contain(point, objects_iterator)) {
			Object * object = objects_iterator->second;
			point_sets[object].erase(point);
			if(point_sets[object].empty()) {
				point_sets.erase(object);
			}
			objects.erase(point);
		}
	}
}

/// Clear all points and objects
//
void Data::clear() {
	objects.clear();
	point_sets.clear();
}

void Data::move(Object * object, Point distance, const Bound & bound) {

	std::cout << "Moving object" << std::endl;
	std::cout << distance << std::endl;
	std::cout << object << std::endl;

	PointSetsIterator point_sets_iterator;
	PointSet next_points;

	if(contain(object, point_sets_iterator)) {
		std::cout << "  has object" << std::endl;
		PointSet & object_points = point_sets_iterator->second;
		typedef std::set<Object *> ObjectsSet;
		ObjectsSet obstacles;
		for( PointSet::iterator
			object_point_iterator = object_points.begin();
			object_point_iterator != object_points.end();
			++object_point_iterator
		) {
			Point next_point = *object_point_iterator + distance;
			next_points.insert(next_point);
			// Check bounds first
			if(!bound.contains(next_point)) {
				return;
			}
			// Check other objects
			ObjectsIterator objects_iterator;
			if(contain(next_point, objects_iterator)) {
				Object * next_object = objects_iterator->second;
				if(object != next_object) {
					obstacles.insert(next_object);
				}
			}
		}
		if(obstacles.empty()) {
			remove(object);
			add(object, next_points, Point(0, 0));
		} else {
			for(ObjectsSet::iterator obstacle = obstacles.begin(); obstacle != obstacles.end(); ++obstacle) {
				PairOfKinds pair_of_kinds(object->kind, (*obstacle)->kind);
				/*Interactions::iterator interaction = game.interactions.find(pair_of_kinds);
				if(interaction->second == PUSH_INTERACTION && !obstacles.contain()) {
				}*/
			}
			/*PairOfKinds interaction_between(this->kind, next_point_information->second->kind);
			Interactions::iterator current_kind_iterator = game.interactions.find(interaction_between);
			if(current_kind_iterator != game.interactions.end()) {
				if(current_kind_iterator->second == PUSH_INTERACTION) {
					if(next_point_information->second->move(_field, _step)) {
						if(move(, next_points, Point(0, 0))) {
							return true;
						}
					}
				}
			}*/
		}
	}

/*	bool Object::move(Field * _field, Point _step) {

		//this_object_info
		//this_point_info
		//next_object_info
		//next_point_info

		//ObjectInformationIterator this_object_info = _field->data.find(this);
		//PointInformationIterator this_point_info = _field->data.find();

		std::cout << "moving..." << std::endl;
		ObjectInformationIterator information = _field->data.objects.find(this);

		if(_field->data.contains(information)) {
			//std::cout << "has object" << std::endl;
			Point next_position = information->second + _step;

			PointInformationIterator next_point_information = _field->data.points.find(next_position);
			if(!_field->data.contains(next_point_information)) {

				// we can move an object to empty cell
				if(_field->bound().contains(next_position)) {
					go_to(_field, next_position);
					return true;
				}

			} else {

					PairOfKinds interaction_between(this->kind, next_point_information->second->kind);
					InteractionMapIterator current_kind_iterator = game.interactions.find(interaction_between);
					if(current_kind_iterator != game.interactions.end()) {

						if(current_kind_iterator->second == PUSH_INTERACTION) {
							if(next_point_information->second->move(_field, _step)) {
								go_to(_field, next_position);
								return true;
							}
						}

					}

			}
			//std::cout << _field->data.objects[this] << std::endl;
		}// else {
		//	std::cout << "has no object" << std::endl;
		//}
		return false;
	}*/

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
