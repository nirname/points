#pragma once

struct ControlHandler {

	ACTION action;
	engine::Point option;

	ControlHandler() {
		action = NO_ACTION;
		option = engine::Point(0, 0);
	}

	~ControlHandler() {
	}

	void evaluate();
	void print(std::ostream &) const;

};

void ControlHandler::print(std::ostream & _ostream) const {
	_ostream << "ControlHandler#" << this << " ("
		<< "action: " << action << ", "
		<< "option: " << option
	<< ")";
}

std::ostream & operator << (std::ostream & _ostream, const ControlHandler & _handler) {
	_handler.print(_ostream);
	return _ostream;
}
