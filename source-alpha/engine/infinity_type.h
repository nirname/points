#pragma once

namespace engine {

	// TODO: Make this types splitted by dimensions
	enum INFINITY_TYPE {
		/// The field is finite
		FINITE,
		/// 'x' is infinite dimension
		HORIZONTAL_INFINITY,
		/// 'y' is infinite dimension
		VERTICAL_INFINITY,
		/// All dimensions of the field are infinite
		FULL_INFINITY
	};

}
