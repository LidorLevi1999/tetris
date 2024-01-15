#pragma once
#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H
class GameConfig
{
public:
	// I'm not sure "DROP" is a needed enum
	enum class eKeys { LEFTP1 = 'a', RIGHTP1 = 'd', LEFTP2 = 'j', RIGHTP2 = 'l', DROP = 'x', ESC = 27, ROTATE_CLOCKWISE = 's', ROTATE_COUNTERCLOCKWISE = 'w' };
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	//Left player board
	static constexpr int MIN_X = 1;
	static constexpr int MIN_Y = 1;

	//Right player board
	static constexpr int RIVAL_MIN_X = MIN_X + 32;

	static const int COLORS[];
	static const int NUM_OF_COLORS;
};
#endif