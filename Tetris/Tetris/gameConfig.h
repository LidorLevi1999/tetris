#pragma once
#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H
class GameConfig
{
public:
	enum class eKeys {
		LEFTP1 = 'a', RIGHTP1 = 'd',
		LEFTP1C = 'A', RIGHTP1C = 'D',
		LEFTP2 = 'j', RIGHTP2 = 'l',
		LEFTP2C = 'J', RIGHTP2C = 'L',
		DROPP1 = 'x', DROPP2 = 'm',
		DROPP1C = 'X', DROPP2C = 'M',
		ROTATE_CLOCKP1 = 's', ROTATE_CLOCKP2 = 'k',
		ROTATE_CLOCKP1C = 'S', ROTATE_CLOCKP2C = 'K',
		ROTATE_COUNTERP1 = 'w', ROTATE_COUNTERP2 = 'i',
		ROTATE_COUNTERP1C = 'W', ROTATE_COUNTERP2C = 'I',
		ESC = 27
	};

	static constexpr int BOARD_HEIGHT = 18;
	static constexpr int BOARD_WIDTH = 12;

	//Left player board
	static constexpr int MIN_X = 1; //
	static constexpr int MIN_Y = 1; //

	//Right player board starting position
	static constexpr int RIVAL_POS = BOARD_WIDTH + 18 + 3;

	static const int COLORS[];
	static int NUM_OF_COLORS;  

	static void setColorSupport(bool isColorSupported);
};
#endif