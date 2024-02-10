// Header file for the User class.

#ifndef __USER_H
#define __USER_H

#include "board.h"

class User
{
	int score;
	char side;

protected:
	Block movingBlock;
	Board board;
	bool checkCopiedBlockCollisionWithBoard(Block& copiedBlock);
public:
	// Constructor
	User(char side);

	// Getter methods
	int getScore() const { return this->score; };
	char getSide() const { return this->side; };
	Block& getMovingBlock() { return this->movingBlock; };
	Board getBoard() { return this->board; };

	// Reset the user's board
	void resetBoard();

	// Update the board and generate a new moving block
	void updateBoardAndGenerateNewBlock();

	// Create a new moving block for the user
	virtual void createNewMovingBlock();

	virtual void handleMovement(GameConfig::eKeys direction = GameConfig::eKeys::NONE) = 0;

	// Move the current moving block based on user input
	bool moveMovingBlock(GameConfig::eKeys direction);

	// Rotate the current moving block
	bool rotateMovingBlock(bool clockWise = true);

	void increaseScore(int scoreReceived) { this->score += scoreReceived; };
	void resetScore() { this->score = 0; };
};

#endif