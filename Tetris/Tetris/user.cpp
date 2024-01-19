#include "user.h"
#include "gameConfig.h"


User::User(char side) {
	this->side = side;
	this->board = Board();
	this->movingBlock = Block(this->side);
	this->board.drawBoard(this->side);
	this->movingBlock.drawBlock();
	this->score = 0;
};


bool User::moveMovingBlock(GameConfig::eKeys direction) {
	Block copyBlock = this->movingBlock;
	int xOffset = copyBlock.getSide() == 'L' ? 0 : GameConfig::RIVAL_POS;
	copyBlock.moveBlock(direction);
	Point* points = copyBlock.getBlockPoints();
	Point p;
	for (int i = 0; i < 4; i++) {
		p = points[i];
		if (p.getY() > GameConfig::BOARD_HEIGHT)
			return false;
		if (p.getX() - (xOffset + 1) < 0)
			return false;
		if (p.getX() > GameConfig::BOARD_WIDTH + xOffset)
			return false;
		if(this->board.getBoard()[(p.getX()-xOffset - 1)][p.getY() - 1] != ' ')
			return false;
	}
	this->movingBlock.copyBlock(copyBlock);
	this->movingBlock.increaseMoveAmount();
	this->movingBlock.drawBlock();
	return true;
}

bool User::rotateMovingBlock(bool clockWise) {
	Block copyBlock = this->movingBlock;
	int xOffset = copyBlock.getSide() == 'L' ? 0 : GameConfig::RIVAL_POS;

	if (clockWise)
		copyBlock.rotateClockwise();
	else copyBlock.rotateCounterClockwise();
	Point* points = copyBlock.getBlockPoints();
	char pointSymbol;
	int xToCheck, yToCheck;
	for (int i = 0; i < 4; i++) {
		xToCheck = points[i].getX() - xOffset;
		yToCheck = points[i].getY() - 1;
		if (xToCheck < 0 || xToCheck > GameConfig::BOARD_WIDTH) return false;
		if (yToCheck < 0 || yToCheck > GameConfig::BOARD_HEIGHT) return false;
		pointSymbol = this->board.getBoard()[(xToCheck)][(yToCheck)];
		if (pointSymbol != ' ')
			return false;
	}
	this->movingBlock.copyBlock(copyBlock);
	this->movingBlock.drawBlock();
	return true;
}


void User::updateBoardAndAssignGenerateNewBlock() {
	this->board.updateBoardWithPoints(this->movingBlock.getBlockPoints());
	this->board.validateBoard();
	this->movingBlock = Block(this->side);
}