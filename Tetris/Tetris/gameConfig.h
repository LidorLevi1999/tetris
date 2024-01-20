#pragma once
#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H
class GameConfig
{
public:
	enum class eKeys {
		LEFTP1 = 'a', RIGHTP1 = 'd',
		LEFTP2 = 'j', RIGHTP2 = 'l',
		DROPP1 = 'x', DROPP2 = 'm',
		ROTATE_CLOCKP1 = 's', ROTATE_CLOCKP2 = 'k',
		ROTATE_COUNTERP1 = 'w', ROTATE_COUNTERP2 = 'i',
		ESC = 27
	};

	static constexpr int BOARD_HEIGHT = 18;
	static constexpr int BOARD_WIDTH = 12;

	//Left player board starting position
	static constexpr int MIN_X = 1;
	static constexpr int MIN_Y = 1;

	//Right player board starting position
	static constexpr int RIVAL_POS = BOARD_WIDTH + 18 + 3;

	static const int COLORS[];
	static int NUM_OF_COLORS;  

	static void setColorSupport(bool isColorSupported);
};
#endif