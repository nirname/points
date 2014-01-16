#pragma once

namespace engine {

	struct Data {

		enum EFFECT_OF_ADDING {
			ADDED_SUCCESSFULLY,
			OBJECT_IS_REPEATED, // it already contains the same object
			OBJECTS_CONFLICT // it has another object at the same position
		};

		ObjectInformation objects; // object with points
		PointInformation points; // points with information about objects

		EFFECT_OF_ADDING add(Object * _object, Point _point) {
			if( !contains(_object) ) {
				if( !contains(_point) ) {
					objects[_object] = _point;
					points[_point] = _object;
					return ADDED_SUCCESSFULLY;
				}
				return OBJECTS_CONFLICT;
			}
			return OBJECT_IS_REPEATED;
		}

		void remove(Object * _object) {
			if( contains(_object) ) {
				// TODO: do something here;
			}
		}

		bool contains(Object * _object) const {
			return objects.find(_object) != objects.end();
		}

		bool contains(const ObjectInformationIterator _iterator) const {
			return _iterator != objects.end();
		}

		bool contains(Point _point) const {
			return points.find(_point) != points.end();
		}

		bool contains(const PointInformationIterator _iterator) const {
			return _iterator != points.end();
		}

	};

}
