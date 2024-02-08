// Implementation file for the User class.


#include "humanUser.h"
#include "gameConfig.h"


// Move the current moving block based on user input
bool HumanUser::moveMovingBlock(GameConfig::eKeys direction) {
	// Create a copy of the current moving block
	Block copyBlock = this->movingBlock;

	// Calculate the X offset based on the side (left or right)
	int xOffset = copyBlock.getSide() == 'L' ? 0 : GameConfig::RIVAL_POS;

	// Move the copied block in the specified direction
	copyBlock.moveBlock(direction);

	// Get the points of the moved block
	const Point* points = copyBlock.getBlockPoints();

	// Check if the moved block is within the game boundaries and does not collide with other blocks
	Point p;
	for (int i = 0; i < 4; i++) {
		p = points[i];
		if (p.getY() > GameConfig::BOARD_HEIGHT)
			return false;
		if (p.getX() - (xOffset + 1) < 0)
			return false;
		if (p.getX() > GameConfig::BOARD_WIDTH + xOffset)
			return false;
		if (this->User::board.getBoard()[(p.getX() - xOffset - 1)][p.getY() - 1].getSymbol() != ' ')
			return false;
	}

	// Update the original moving block with the moved block
	this->movingBlock.copyBlock(copyBlock);
	this->movingBlock.increaseMoveAmount();
	this->movingBlock.drawBlock();
	return true;
}

// Rotate the current moving block
bool HumanUser::rotateMovingBlock(bool clockWise) {
	// Create a copy of the current moving block
	Block copyBlock = this->movingBlock;

	// Calculate the X offset based on the side (left or right)
	int xOffset = copyBlock.getSide() == 'L' ? 1 : GameConfig::RIVAL_POS + 1;

	// Rotate the copied block either clockwise or counterclockwise
	if (clockWise)
		copyBlock.rotateClockwise();
	else
		copyBlock.rotateCounterClockwise();

	// Get the points of the rotated block
	const Point* points = copyBlock.getBlockPoints();
	char pointSymbol;

	// Check if the rotated block is within the game boundaries and does not collide with other blocks
	int xToCheck, yToCheck;
	for (int i = 0; i < 4; i++) {
		xToCheck = points[i].getX() - xOffset;
		yToCheck = points[i].getY() - 1;
		if (xToCheck < 0 || xToCheck > GameConfig::BOARD_WIDTH - 1) return false;
		if (yToCheck < 0 || yToCheck >= GameConfig::BOARD_HEIGHT) return false;
		pointSymbol = this->User::board.getBoard()[(xToCheck)][(yToCheck)].getSymbol();
		if (pointSymbol != ' ')
			return false;
	}

	// Update the original moving block with the rotated block
	this->movingBlock.copyBlock(copyBlock);
	this->movingBlock.drawBlock();
	return true;
}
