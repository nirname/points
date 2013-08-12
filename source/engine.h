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
#include "engine/level.h"

#include "engine/game.h"

// engine
namespace engine {

	void Object::display(const Point & _position = Point()) { //, const Animation & = NULL
		glPushMatrix();
			glTranslatef(_position.column, _position.row, 0);
			glPushAttrib(GL_CURRENT_BIT);
				//graphics::use_color(color);
				use_color();
				glPushMatrix(); // animation goes here
					/*for(AnimationList::iterator a = animations.begin(); a != animations.end(); ++a) {
						(*a)->apply();
					}*/
					//game.animations["Scale"]->apply();
					/*glTranslatef(0.5, 0.5, 0);
					glScalef(scale, scale, 0);
					glTranslatef(-0.5, -0.5, 0);*/
					//draw_shape();
					graphics::square();
				glPopMatrix();
				glPopAttrib();
		glPopMatrix();
	}

	/*bool Object::move(Field * _field, Point _step, graphics::Animation * _animation) {
	}*/

	/*bool Object::move(Field *, Point _step, graphics::Animation * _animation) {
		_animation->start();
	};*/

	void Object::go_to(Field * _field, Point _target) {
		// !!! use animations here
		ObjectInformationIterator information = _field->data.objects.find(this);
		_field->data.points.erase(information->second);
		information->second = _target;
		_field->data.points[_target] = this;
	};

	// !!! optimize this part
	// !!! rename objects and points collections
	// use stack?
	bool Object::move(Field * _field, Point _step) {

		//this_object_info
		//this_point_info
		//next_object_info
		//next_point_info

		//ObjectInformationIterator this_object_info = _field->data.find(this);
		//PointInformationIterator this_point_info = _field->data.find();

		//std::cout << "moving..." << std::endl;
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

} // engine

#endif
