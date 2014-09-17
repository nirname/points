#pragma once

namespace engine {

	// TODO: Make this types splitted by dimensions
	enum CLOSURE_TYPE {
		/// Describes regular field,
		/// where objects can not move outside of bounds.
		NO_CLOSURE,
		/// If an object goes beyond the boundaries of the field
		/// while moving 'x' coordinate
		/// it'll be places at the opposite side.
		HORIZONTAL_CLOSURE,
		/// If an object goes beyond the boundaries of the field
		/// while moving 'y' coordinate
		/// it'll be places at the opposite side.
		VERTICAL_CLOSURE,
		/// It is combination of all closure types.
		FULL_CLOSURE
	};

}
