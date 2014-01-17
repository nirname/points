#pragma once

// Game logic
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
		BOMBERMAN,
		PACMAN,

		// Multiplayer

		REVERSI,
		GOMOKU,
		FOUR_IN_A_ROW,
		TRHONE,
		BATTLESHIP,
		POINTS,
		GO,
		STICS,
		CORNERS,

		// Screensavers

		LIVE,
		QUEENS,
		GEOGRAPHIC_EARTH_MAP,
		DAY_NIGHT_EARTH_MAP,
		POLITICAL_EARTH_MAP,
		TURTLE,
		EQUALIZER,
		TIMER

	};

}
