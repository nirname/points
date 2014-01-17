#pragma once

enum PROGRAM_MODE {
	DISABLED_MODE,    // Nothing to do
	LOADING_MODE,     // Game is being loaded now
	TITRES_MODE,      // Introduction, Finale
	MENU_MODE,        // Main menu, Game menu, Level menu
	SCREENSAVER_MODE, // Any screensaver
	GAMEPLAY_MODE,    // Gameplay itself, Countdown?
	INFORMATION_MODE  // Pause, Completion, Looser, Winner // TODO: remove it?
};
