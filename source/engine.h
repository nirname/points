#ifndef ENGINE_H
#define ENGINE_H 1

#include "engine/base.h"
#include "engine/object_kind.h"
#include "engine/object.h"
#include "engine/data.h"
#include "engine/field.h"
#include "engine/view.h"
#include "engine/screen.h"
#include "engine/level.h"
#include "engine/control_handler.h"

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
					draw_shape();
					//graphics::square();
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
	}

	void ControlHandler::evaluate() {
		std::cout << ": eval\n";
		for(FieldMapping::Iterator iterator = game.fields.begin(); iterator != game.fields.end(); ++iterator) {
			std::cout << iterator->second << std::endl;
			object->move(iterator->second, option);
		}
	}

	void operator >> (const YAML::Node & options, Size & size) {
		try {
			if(options.IsMap()) {
				if(options["width"] != NULL && options["height"] != NULL) {
					size.width = options["width"].as<int>();
					size.height = options["height"].as<int>();
				}
			} else if (options.IsSequence()) {
				if(options.size() == 1) {
					size.height = size.width = options[0].as<int>();
				} else if(options.size() == 2) {
					size.width = options[0].as<int>();
					size.height = options[1].as<int>();
				} else {
					std::cout << "Wrong number of arguments for size" << std::endl;
				}
			} else if (options.IsScalar()) {
				size.height = size.width = options.as<int>();
			} else {
				std::cout << "Size options should be scalar or map" << std::endl;
			}
		} catch(YAML::TypedBadConversion<int> & exception) {
			std::cout << "Size should be an integer " << std::endl;
			size.width = 1;
			size.height = 1;
		}
		if(size.width <= 0) {
			size.width = 1;
			std::cout << "Any size dimension should be greater than 0" << std::endl;
		}
		if(size.height <= 0) {
			size.height = 1;
			std::cout << "Any size dimension should be greater than 0" << std::endl;
		}
	}

	void operator >> (const YAML::Node & options, Point & point) {
		try {
			if(options.IsMap()) {
				if(options["row"] != NULL && options["column"] != NULL) {
					point.row = options["row"].as<int>();
					point.column = options["column"].as<int>();
				}
			} else if (options.IsSequence()) {
				if(options.size() == 1) {
					point.column = point.row = options[0].as<int>();
				} else if(options.size() == 2) {
					point.column = options[0].as<int>();
					point.row = options[1].as<int>();
				} else {
					std::cout << "Wrong number of arguments for point" << std::endl;
				}
			} else if (options.IsScalar()) {
				point.column = point.row = options.as<int>();
			} else {
				std::cout << "Point options should be scalar or map" << std::endl;
			}
		} catch(YAML::TypedBadConversion<int> & exception) {
			std::cout << "Point dimension should be an integer " << std::endl;
		}
	}

	void operator >> (const YAML::const_iterator & iterator, Data & data) {
		ObjectPointer object = game.objects[iterator->first.as<std::string>()];
		if(object != NULL) {
			Point point;
			iterator->second >> point;
			Data::EFFECT_OF_ADDING effect = data.add(object, point);
			if(effect != Data::ADDED_SUCCESSFULLY) {
				std::cout << "Some problems occured while adding object" << std::endl;
			}
		}
	}

	void operator >> (const YAML::Node & options, Field & field) {
		if(options.IsMap()) {
			if(options["size"]) {
				options["size"] >> field.size;
			}
			if(options["closure"]) {
			}
			if(options["data"]) {
				const YAML::Node & data_node = options["data"];
				if(data_node.IsMap()) {
					for(YAML::const_iterator iterator = data_node.begin(); iterator != data_node.end(); ++iterator) {
						iterator >> field.data;
					}
				}
			}
		} else {
			std::cout << "Options for field should be a mapping" << std::endl;
		}
	}

	void operator >> (const YAML::Node& options, ObjectKind & object_kind) {
		if(options["color"]) {
			object_kind.color = game.colors[options["color"].as<std::string>()];
		}
		if(options["shape"]) {
			object_kind.shape = game.shapes[options["shape"].as<std::string>()];
		}
	}

	void operator >> (const YAML::Node & options, View & view) {
		if(options.IsMap()) {
			view.field = game.fields[options["field"].as<std::string>()];
			if(options["size"]) {
				options["size"] >> view.size;
			} else {
				view.adjust_size();
			}
			if(options["offset"]) {
				options["offset"] >> view.offset;
			}
			if(options["position"]) {
				options["position"] >> view.position;
			}
		} else {
			std::cout << "Options for view should be a mapping" << std::endl;
		}
	}

	void operator >> (const YAML::Node & options, ControlHandler & handler) {
		if(options.IsMap()) {
			if(options["object"]) handler.object = game.objects[options["object"].as<std::string>()];
			if(options["action"]) handler.action = MOVE;
			if(options["option"]) options["option"] >> handler.option;
		}
		//ObjectPointer object = game.objects[->first.as<std::string>()];
		//if(object != NULL) {
			//YAML::NodeType::value node_type = iterator->second.Type();
		//}
	}

	/*struct Cell
	{
		graphics::Color * color;
		//graphics::Shape * shape;
		//Cell(graphics::Color _color, graphics::Shape * shape)
	};*/

} // engine

#endif
