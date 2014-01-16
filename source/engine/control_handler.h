// TODO move it from here

#pragma once

namespace engine {

	enum ACTION_NAME {
		NO_ACTION,
		MOVE
	};

	struct ControlHandler {
		/*Mapping<ActionOptions> actions; // actions with it's options
		std::list<EntityIdentifier> entities;*/
		engine::ObjectPointer object;
		ACTION_NAME action;
		engine::Point option;

		ControlHandler() {
			object = NULL;
			action = NO_ACTION;
			option = engine::Point(0, 0);
		}

		void evaluate();

		void print(std::ostream & _ostream) const {
			_ostream << "ControlHandler#" << this << " ("
				<< "object: " << object << ", "
				<< "action: " << action << ", "
				<< "option: " << option
			<< ")";
		}

	};

	std::ostream & operator << (std::ostream & _ostream, const ControlHandler & _handler) {
		_handler.print(_ostream);
		return _ostream;
	}

}
