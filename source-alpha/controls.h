#pragma once

namespace controls {

	class Key;

	class Key {
		unsigned char value;
		int special;

		//bool operator < (const Key &) const;
	};

	//bool Key::operator < (const Key & _key) const {
	//}

	#include "controls/action.h"
	#include "controls/control_handler.h"

}
