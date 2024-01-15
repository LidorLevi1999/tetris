#ifndef __BOARD_H
#define __BOARD_H
#include "block.h"

class Board {
private:
	Point board[GameConfig::GAME_WIDTH][GameConfig::GAME_HEIGHT];
	Block movingBlock;

	void drawTPHBorders();
	void drawLRVBorders();
	void drawScore();
public:
	bool checkIfBlockCanMove();
	bool validateBoard();
	
	void drawBordersAndScore();

private:
};



#endif