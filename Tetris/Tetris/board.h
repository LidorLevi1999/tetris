// Header file for the Board class, representing the Tetris game board.

#ifndef __BOARD_H
#define __BOARD_H

#include "block.h"

class Board 
{
private:
	Point board[GameConfig::BOARD_WIDTH][GameConfig::BOARD_HEIGHT];
	char side;

public:
	// Constructor
	Board(char side);

	const Point(*getBoard())[GameConfig::BOARD_HEIGHT] { return this->board; };

	// Clears the entire game board
	void clearBoard();

	// Draws the game board, including borders and current block positions
	void drawBoard(char side);

	// Updates the game board with the current block's points
	void updateBoardWithPoints(const Point* const& points);

	// Validates and clears full rows, updating the board and returning the score
	int validateBoard();

	void performBombExplosion(const Point& bombPosition);
private:
	// Checks if a given row is completely filled with blocks
	bool isAllRowFull(int row) const;

	// Clears a filled row and shifts the above rows down
	void bombRowAndFixBoard(int row);
	
	//update all board points afterh the explosion
	void updateBoardPointsAfterExplosion();

	//Drop all points down;
	void dropPointsDown(int col);
};
#endif