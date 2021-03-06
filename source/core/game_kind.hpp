#pragma once

#define SINGLE_PLAYER_GAME 0x100
#define MULTI_PLAYER_GAME  0x200
#define MIXED_GAME         0x300

enum GAME_KIND {
	NO_GAME = 0,

	TETRIS = SINGLE_PLAYER_GAME,
	LIGHTS,
	ROBOTS,
	SWAP,
	RUSH_HOUR,
	ATOMIX,
	POLYMINO,
	BACKGROUND,
	LINES,
	NETWALK,
	MOWER,
	MASYU,
	RINGS,
	PACMAN,
	GAME1024,
	GAME1010,

	REVERSI = MULTI_PLAYER_GAME,
	GOMOKU,
	FOUR_IN_A_ROW,
	TRHONE,
	BATTLESHIP,
	//POINTS,
	GO,
	STICS,
	CORNERS,

	SNAKE = MIXED_GAME,
	SOKOBAN,
	LABYRINTH,
	BOMBERMAN
};

const GAME_KIND all_game_kinds [] = {
	TETRIS,
	LIGHTS,
	ROBOTS,
	SWAP,
	RUSH_HOUR,
	ATOMIX,
	POLYMINO,
	BACKGROUND,
	LINES,
	NETWALK,
	MOWER,
	MASYU,
	RINGS,
	PACMAN,
	GAME1024,
	GAME1010,

	REVERSI,
	GOMOKU,
	FOUR_IN_A_ROW,
	TRHONE,
	BATTLESHIP,
	//POINTS,
	GO,
	STICS,
	CORNERS,

	SNAKE,
	SOKOBAN,
	LABYRINTH,
	BOMBERMAN
};
