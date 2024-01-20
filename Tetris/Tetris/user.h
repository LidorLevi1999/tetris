#ifndef __USER_H
#define __USER_H
#include "board.h"
class User
{
	int score;
	char side;
	Block movingBlock;
	Board board;
public:
	User(char side);
	int getScore() const { return this->score; };
	int	getSide() const { return this->side; };
	Block& getMovingBlock() { return this->movingBlock; };
	Board getBoard() { return this->board; };
	bool moveMovingBlock(GameConfig::eKeys direction);
	void updateBoardAndAssignGenerateNewBlock();
	bool rotateMovingBlock(bool clockWise = true);
	void createNewMovingBlock();
	void resetBoard();
	void increaseScore(int scoreRecieved) { this->score += scoreRecieved; };
	void resetScore() { this->score = 0; };
public:
private:

};

#endif