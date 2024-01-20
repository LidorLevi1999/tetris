#include "gameConfig.h"

#include <Windows.h>

const int GameConfig::COLORS[] = { FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, 96, 176, 224, 95, 23, 111, 143, 48 };
int GameConfig::NUM_OF_COLORS = sizeof(COLORS) / sizeof(int);

void GameConfig::setColorSupport(bool isColorSupported) {
	GameConfig::NUM_OF_COLORS = isColorSupported ? sizeof(COLORS) / sizeof(int) : 1;
}
