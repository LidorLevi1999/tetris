#ifndef __BOARD_H
#define __BOARD_H
#include "block.h"

class Board {
private:
	Point board[GameConfig::GAME_WIDTH][GameConfig::GAME_HEIGHT];
	Block movingBlock;
public:
	bool checkIfBlockCanMove();
	bool validateBoard();
private:
};



#endif