#pragma once

/// Game mode
//
/// 0x01 - single player game only
/// 0x10 - multi player game only or vs a computer
/// 0x11 - single or multi player game
///
enum GAME_MODE {
	UNDEFINED_GAME     = 0x00,
	SINGLE_PLAYER_GAME = 0x01,
	MULTI_PLAYER_GAME  = 0x10,
	MIXED_GAME         = 0x11
};

/// Game kind
//
/// All the games
enum GAME_KIND {
	NO_GAME       = 0x0000,
	SNAKE         = 0x0100,
	SOKOBAN       = 0x0200,
	ATOMIX        = 0x0300,
	RUSH_HOUR     = 0x0400,
	LIGHTS        = 0x0500,
	TETRIS        = 0x0600,
	ROBOTS        = 0x0700,
	LABYRINTH     = 0x0800,
	SWAP          = 0x0900,
	POLYMINO      = 0x0A00,
	BACKGROUND    = 0x0B00,
	LINES         = 0x0C00,
	NETWALK       = 0x0D00,
	MOWER         = 0x0E00,
	MASYU         = 0x0F00,
	RINGS         = 0x1000,
	BOMBERMAN     = 0x1100,
	PACMAN        = 0x1200,
	GAME1024      = 0x1300,
	GAME1010      = 0x1400,
	REVERSI       = 0x1500,
	GOMOKU        = 0x1600,
	FOUR_IN_A_ROW = 0x1700,
	TRHONE        = 0x1800,
	BATTLESHIP    = 0x1900,
	POINTS        = 0x1A00,
	GO            = 0x1B00,
	STICS         = 0x1C00,
	CORNERS       = 0x1D00
};

/*enum GAME_KIND {
	NO_GAME       = 0x0000,
	SNAKE         = 0x0111,
	SOKOBAN       = 0x0211,
	ATOMIX        = 0x0301,
	RUSH_HOUR     = 0x0401,
	LIGHTS        = 0x0501,
	TETRIS        = 0x0601,
	ROBOTS        = 0x0701,
	LABYRINTH     = 0x0811,
	SWAP          = 0x0901,
	POLYMINO      = 0x0A01,
	BACKGROUND    = 0x0B01,
	LINES         = 0x0C01,
	NETWALK       = 0x0D01,
	MOWER         = 0x0E01,
	MASYU         = 0x0F01,
	RINGS         = 0x1001,
	BOMBERMAN     = 0x1111,
	PACMAN        = 0x1201,
	GAME1024      = 0x1301,
	GAME1010      = 0x1401,
	REVERSI       = 0x1510,
	GOMOKU        = 0x1610,
	FOUR_IN_A_ROW = 0x1710,
	TRHONE        = 0x1810,
	BATTLESHIP    = 0x1910,
	POINTS        = 0x1A10,
	GO            = 0x1B10,
	STICS         = 0x1C10,
	CORNERS       = 0x1D10
};*/
