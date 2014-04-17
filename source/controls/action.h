#pragma once

enum ACTION {
	/// Nothing to do
	NO_ACTION,
	/// Move an object at a given distance. Relative value
	MOVE_ACTION,
	/// Move an object to a given point
	GO_TO_ACTION,
	/// Rotate an object or change a direction (for instance, snake direction)
	TURN_ACTION,
	/// Flip an object along specified axies
	REFLECT_ACTION,
	/// Move tail of an object to head
	STEP_ACTION,
	/// Swap tail and head of object
	REVERSE_ACTION
};
