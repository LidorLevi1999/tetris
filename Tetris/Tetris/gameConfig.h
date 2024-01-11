#pragma once
#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H
class GameConfig
{
public:
	enum class eKeys { LEFT = 'a', RIGHT = 'd', DOWN = 'x', ESC = 27, ROTATE_CLOCKWISE = 's', ROTATE_COUNTERCLOCKWISE = 'w' };
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	static constexpr int MIN_X = 0;
	static constexpr int MIN_Y = 0;

	static const int COLORS[];
	static const int NUM_OF_COLORS;
};
#endif