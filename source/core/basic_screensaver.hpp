#pragma once

#include "size.hpp"

struct BasicScreensaver {

	Size size;

	BasicScreensaver();
	virtual ~BasicScreensaver() = 0;

	virtual void display() = 0;

};
