#pragma once

#include "engine/base.h"


#include "engine/cell.h"
#include "engine/object_kind.h"
#include "engine/object.h"
#include "engine/interaction.h"
#include "engine/data.h"
#include "engine/_data.h"
#include "engine/closure_type.h"
#include "engine/field.h"
#include "engine/view.h"
#include "engine/control_handler.h"

#include "engine/game.h"

// engine
// TODO: move it from here
namespace engine {

	// TODO: replace it
	void ControlHandler::evaluate() {
		std::cout << ": eval\n";
		// TODO: this part does not work properly;
		// TODO: use current view or first view or something like that
		//
		/*for(FieldMapping::Iterator iterator = game.fields.begin(); iterator != game.fields.end(); ++iterator) {
			std::cout << iterator->second << std::endl;
			object->move(iterator->second, option);
		}*/
	}

} // engine
