#ifndef LOGIC_H
#define LOGIC_H 1

// game logic
// (!!!) remove logic file at all?
namespace logic {

	enum GAME_KIND {

		// Single player

		SNAKE = 0x00,
		SOKOBAN,
		ATOMIX,
		RUSH_HOUR,
		LIGHTS,
		TETRIS,
		ROBOTS,
		LABYRINTH,
		SWAP,
		POLYMINO,
		BACKGROUND,
		LINES,
		NETWALK,
		MOWER,
		MASYU,
		RINGS,

		// Multiplayer

		REVERSI = 0x20,
		GOMOKU,
		FOUR_IN_A_ROW,
		TRHONE,
		BATTLESHIP,
		POINTS,
		GO,
		STICS,
		CORNERS,

		// Screensavers

		LIVE = 0x40,
		QUEENS,
		GEOGRAPHIC_EARTH_MAP,
		DAY_NIGHT_EARTH_MAP,
		POLITICAL_EARTH_MAP,
		TURTLE,
		EQUALIZER,
		TIMER

	};

}

#endif
