#pragma once

#include "player_action.hpp"
#include <map>

typedef unsigned char Key;
typedef std::string Player;

typedef std::map <Key, PLAYER_ACTION> Controls;
typedef std::map <Player, Controls> PlayersControls;

namespace options {
	PlayersControls players_controls;
}
