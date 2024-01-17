#ifndef __BOARD_H
#define __BOARD_H
#include "block.h"

class Board 
{
private:
	char board[GameConfig::BOARD_WIDTH][GameConfig::BOARD_HEIGHT];
	char side;
	Block movingBlock;

public:
	Board();
	void drawBoard(char side);
	void drawScore(); //
	bool checkIfBlockCanMove();
	bool validateBoard();

private:
};



#endif