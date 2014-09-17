#pragma once

void operator >> (const std::string & value, GAME_KIND & _game_kind) {
	for(GAME_KIND iterator = NO_GAME; iterator <= CORNERS; iterator++) {
		if(value == lib::to_string(iterator)) {
			_game_kind = iterator;
			break;
		}
	}
}
