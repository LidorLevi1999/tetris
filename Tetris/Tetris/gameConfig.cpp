// Implementation file for the GameConfig class.

#include "gameConfig.h"
#include <Windows.h>

// Array of color values for blocks
const int GameConfig::COLORS[] = { FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, 96, 176, 224, 95, 23, 111, 143, 48 };

// Number of available colors (initialized based on color support)
int GameConfig::NUM_OF_COLORS = sizeof(COLORS) / sizeof(int);

// Set the number of colors based on color support
void GameConfig::setColorSupport(bool isColorSupported) {
	NUM_OF_COLORS = isColorSupported ? sizeof(COLORS) / sizeof(int) : 1;
}
