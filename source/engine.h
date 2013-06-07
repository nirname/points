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
	bool Object::move(Field * _field, Point _step) {
		/*Placement placement(this, _field);
		Point * position = game.points[placement];
		if(position != NULL && _field->bound().contains(*position + _step)) {
			*(position) += _step;
		}*/

		//this_object_info
		//next_object_info
		//this_point_info
		//next_point_info

		//std::cout << "moving..." << std::endl;
		ObjectsInformationIterator information = _field->data.objects.find(this);

		if(_field->data.contains(information)) {
			//std::cout << "has object" << std::endl;
			Point next_position = information->second + _step;
			PointsInformationIterator next_point_information = _field->data.points.find(next_position);
			if(!_field->data.contains(next_point_information)) {

				// we can move an object to empty cell
				if(_field->bound().contains(next_position)) {
					_field->data.points.erase(information->second);
					information->second = next_position;
					_field->data.points[information->second] = this;
					return true;
				}

			} else {

					// use interactions here
					PairOfKinds interaction_between(this->kind, next_point_information->second->kind);
					//InteractionMapIterator current_kind_iterator = game.interactions.find(interaction_between);
					//if(current_kind_iterator != game.interactions.end())
						//if(current_kind_iterator->second == PUSH_INTERACTION) {
							if(next_point_information->second->move(_field, _step)) {
								_field->data.points.erase(information->second);
								information->second = next_position;
								_field->data.points[information->second] = this;
								return true;
							}
						//}
					//}

			}
			//std::cout << _field->data.objects[this] << std::endl;
		}/* else {
			//std::cout << "has no object" << std::endl;
		}*/
		return false;
	}

	/*struct Cell
	{
		graphics::Color * color;
		//graphics::Shape * shape;
		//Cell(graphics::Color _color, graphics::Shape * shape)
	};*/

	struct Level {
		std::string name;
		bool load() {
			return false;
		}
	};


} // engine

#include "engine/game.h"

#endif
