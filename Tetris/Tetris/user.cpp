// Implementation file for the User class.


#include "user.h"
#include "gameConfig.h"

// Constructor
User::User(char side):	board(Board(side)){
	this->side = side;
	this->score = 0;
	this->didImove = false;
};

// Reset the user's board
void User::resetBoard() {
	this->board = Board(this->side);
}

// Move the current moving block based on user input
bool User::moveMovingBlock(GameConfig::eKeys direction) {
	// Create a copy of the current moving block
	Block copyBlock = this->movingBlock;

	// Move the copied block in the specified direction
	copyBlock.moveBlock(direction);

	if (!checkCopiedBlockCollisionWithBoard(copyBlock))
		return false;

	// Update the original moving block with the moved block
	this->movingBlock.copyBlock(copyBlock);
	this->movingBlock.increaseMoveAmount();
	this->movingBlock.drawBlock();
	return true;
}

// Rotate the current moving block
bool User::rotateMovingBlock(bool clockWise) {
	// Create a copy of the current moving block
	Block copyBlock = this->movingBlock;

	// Rotate the copied block either clockwise or counterclockwise
	if (clockWise)
		copyBlock.rotateClockwise();
	else
		copyBlock.rotateCounterClockwise();


	if (!checkCopiedBlockCollisionWithBoard(copyBlock))
		return false;

	// Update the original moving block with the rotated block
	this->movingBlock.copyBlock(copyBlock);
	this->movingBlock.drawBlock();
	return true;
}

// Update the board and generate a new moving block
void User::updateBoardAndGenerateNewBlock() {
	// Update the board with the points of the current moving block
	if (this->movingBlock.getIsBomb()) {
		this->board.performBombExplosion(this->movingBlock.getBlockPoints()[0]);
		this->board.drawBoard(this->getSide());
	}
	else {
		this->board.updateBoardWithPoints(this->movingBlock.getBlockPoints());
	}
	// Validate the board and receive points
	int pointsReceived = this->board.validateBoard();

	// Increase the user's score
	this->increaseScore(pointsReceived);

	// Create a new moving block for the user
	createNewMovingBlock();
}

// Create a new moving block for the user
void User::createNewMovingBlock() {
	this->movingBlock = Block(this->side);
}

// Check if the rotated block is within the game boundaries and does not collide with other blocks
bool User::checkCopiedBlockCollisionWithBoard(Block& copiedBlock) {
	// Get the points of the rotated block
	const Point* points = copiedBlock.getBlockPoints();
	char pointSymbol;
	int xOffset = copiedBlock.getSide() == 'L' ? 1 : GameConfig::RIVAL_POS + 1;
	int xToCheck, yToCheck;
	for (int i = 0; i < 4; i++) {
		xToCheck = points[i].getX() - xOffset;
		yToCheck = points[i].getY() - 1;
		if (xToCheck < 0 || xToCheck > GameConfig::BOARD_WIDTH - 1) return false;
		if (yToCheck < 0 || yToCheck >= GameConfig::BOARD_HEIGHT) return false;
		pointSymbol = this->board.getBoard()[(xToCheck)][(yToCheck)].getSymbol();
		if (pointSymbol != EMPTY_SPACE)
			return false;
	}
	return true;
}

