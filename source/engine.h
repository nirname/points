#ifndef ENGINE_H
#define ENGINE_H 1

namespace engine {

	
	
	/*struct Interaction {
		ObjectKindType first_type;
		ObjectKindType second_type;
	};*/
	
	
}

#include "engine/base.h"
#include "engine/object.h"
#include "engine/data.h"
#include "engine/field.h"
#include "engine/view.h"
#include "engine/screen.h"

// engine
namespace engine {

	//!!! optimize this part
	void Object::move(Field * _field, Point _step) {
		/*Placement placement(this, _field);
		Point * position = game.points[placement];
		if(position != NULL && _field->bound().contains(*position + _step)) {
			*(position) += _step;
		}*/
		
		//std::cout << "moving..." << std::endl;
		ObjectsInformationIterator information = _field->data.objects.find(this);
		if(_field->data.contains(information)) {
			//std::cout << "has object" << std::endl;
			Point next_position = information->second + _step;
			if(!_field->data.contains(next_position)) {
				// use interactions here
				if(_field->bound().contains(next_position)) {
					_field->data.points.erase(information->second);
					information->second += _step;
					_field->data.points[information->second] = this;
				}
			}
			//std::cout << _field->data.objects[this] << std::endl;
		}/* else {
			//std::cout << "has no object" << std::endl;
		}*/
	}

	/*struct Cell
	{
		graphics::Color * color;
		//graphics::Shape * shape;
		//Cell(graphics::Color _color, graphics::Shape * shape)
	};*/

	// Link between object and field
	/*struct Placement
	{
		Object * object;
		Field * field;
		Placement(Object * _object, Field * _field):
			object(_object), field(_field)
		{}
		std::string hash();
	};
	
	std::string Placement::hash() {
		if (object == NULL || field == NULL) {
			return std::string();
		}
		else {
			return std::string(lib::to_string(object->number) + lib::to_string(field->number));
		}
	}

	bool operator < (Placement a, Placement b) {
		return a.hash() < b.hash();
	}*/


	// Contains width and height expressed by count of horizontal and vertical squares
	
	

	struct Level {
		std::string name;
		bool load() {
			return false;
		}
	};
	

} // engine

#include "engine/game.h"

#endif
