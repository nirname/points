#ifndef DATA_H
#define DATA_H 1

namespace engine {

	struct Data {
		
		enum EFFECT_OF_ADDING {
			ADDED_SUCCESSFULLY,
			OBJECT_IS_REPEATED, // it already contains the same object
			OBJECTS_CONFLICT // it has another object at the same position
		};
		
		ObjectsInformation objects; // object with points
		PointsInformation points; // points with information about objects
		/*void contains() {}*/
		EFFECT_OF_ADDING add(Object * _object, Point _point) {
			if( objects.find(_object) == objects.end() ) {
				if( points.find(_point) == points.end() ) {
					objects[_object] = _point;
					points[_point] = _object;
					return ADDED_SUCCESSFULLY;
				}
				else {
					return OBJECTS_CONFLICT;
				}
			} else {
				return OBJECT_IS_REPEATED;
			}
		}
		
		void remove(Object * _object) {
			
		}
		
		bool contains(Object * _object) const {
			return objects.find(_object) != objects.end();
		}
		
		bool contains(const ObjectsInformationIterator _position) const {
			return _position != objects.end();
		}
		
		bool contains(Point _point) const {
			return points.find(_point) != points.end();
		}

	};

}

#endif