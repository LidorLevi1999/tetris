#ifndef __BOARD_H
#define __BOARD_H
#include "block.h"

class Board 
{
private:
	Point board[GameConfig::BOARD_WIDTH][GameConfig::BOARD_HEIGHT];
	char side;

public:
	Board(char side);
	void drawBoard(char side);
	int validateBoard();
	const Point(*getBoard())[GameConfig::BOARD_HEIGHT] { return this->board; };
	void updateBoardWithPoints(Point* points);
	void clearBoard();

private:
	bool isAllRowFull(int row) const;
	void bombRowAndFixBoard(int row);
};
#endif