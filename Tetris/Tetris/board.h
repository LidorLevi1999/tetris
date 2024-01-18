#ifndef __BOARD_H
#define __BOARD_H
#include "block.h"

class Board 
{
private:
	char board[GameConfig::BOARD_WIDTH][GameConfig::BOARD_HEIGHT];
	char side;

public:
	Board();
	void drawBoard(char side);
	//void drawScore(); 
	void validateBoard();
	const char(*getBoard())[GameConfig::BOARD_HEIGHT] { return this->board; };
	void updateBoardWithPoints(Point* points);
private:
	bool isAllRowFull(int row) const;
	void bombRowAndFixBoard(int row);
};



#endif