#pragma once

enum ACTION_KIND {
	/// Nothing to do
	NO_ACTION,
	/// Move an object at a given distance. Relative value
	MOVE_ACTION,
	/// Move an object to a given point
	GO_TO_ACTION,
	/// Rotate an object
	ROTATE_ACTION,
	/// Flip an object along specified axies
	REFLECT_ACTION
};
