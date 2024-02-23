// Implementation file for the Block class.

#include "block.h"
#include "gameConfig.h"
#include "general.h"
#include <array>

// Constructor;
Block::Block(char side) {
	// Initialize member variables
	this->side = side;
	this->blockShape = getRandomShape();
	this->rotateRightAmount = 0;
	this->movedAmount = 0;
	this->isBomb = this->blockShape == Block::eTetriminoShape::Bomb;
	// Choose a random color for the block
	int randomValue = rand() % GameConfig::NUM_OF_COLORS;
	this->blockColor = this->isBomb ? GameConfig::COLORS[0] : GameConfig::COLORS[randomValue];

	// Build the block points based on its shape
	buildBlockPoints();
}

// Build the 4 points of the block.//
// Assume that a block is being created only at the middle top of the board.
void Block::buildBlockPoints() {
	int middleX = (GameConfig::BOARD_WIDTH + 1) / 2;
	if (this->side == 'R')
		middleX += GameConfig::RIVAL_POS;

	this->points[0] = Point(middleX, 2, TETRIMINO_SYMBOL, this->blockColor);

	switch (this->blockShape) {
	case eTetriminoShape::O:
		generate3NonCenterPoints(Point(middleX + 1, 2, TETRIMINO_SYMBOL, this->blockColor), Point(middleX + 1, 1, TETRIMINO_SYMBOL, this->blockColor), Point(middleX , 1, TETRIMINO_SYMBOL, this->blockColor));
		break;
	case eTetriminoShape::T:
		generate3NonCenterPoints(Point(middleX - 1, 2, TETRIMINO_SYMBOL, this->blockColor), Point(middleX + 1, 2, TETRIMINO_SYMBOL, this->blockColor), Point(middleX, 1, TETRIMINO_SYMBOL, this->blockColor));
		break;
	case eTetriminoShape::L:
		generate3NonCenterPoints(Point(middleX - 1, 2, TETRIMINO_SYMBOL, this->blockColor), Point(middleX + 1, 2, TETRIMINO_SYMBOL, this->blockColor), Point(middleX + 1, 1, TETRIMINO_SYMBOL, this->blockColor));
		break;
	case eTetriminoShape::J:
		generate3NonCenterPoints(Point(middleX - 1, 1, TETRIMINO_SYMBOL , this->blockColor), Point(middleX - 1, 2, TETRIMINO_SYMBOL, this->blockColor), Point(middleX + 1, 2, TETRIMINO_SYMBOL, this->blockColor));
		break;
	case eTetriminoShape::S:
		generate3NonCenterPoints(Point(middleX - 1, 2, TETRIMINO_SYMBOL, this->blockColor), Point(middleX , 1, TETRIMINO_SYMBOL, this->blockColor), Point(middleX + 1, 1, TETRIMINO_SYMBOL, this->blockColor));
		break;
	case eTetriminoShape::Z:
		generate3NonCenterPoints(Point(middleX - 1, 1 , TETRIMINO_SYMBOL, this->blockColor), Point(middleX, 1, TETRIMINO_SYMBOL, this->blockColor), Point(middleX + 1, 2, TETRIMINO_SYMBOL, this->blockColor));
		break;
	case eTetriminoShape::I:
		this->points[0] = Point(middleX, 1, TETRIMINO_SYMBOL, this->blockColor);
		generate3NonCenterPoints(Point(middleX - 1, 1, TETRIMINO_SYMBOL, this->blockColor), Point(middleX + 1, 1, TETRIMINO_SYMBOL, this->blockColor), Point(middleX + 2, 1, TETRIMINO_SYMBOL, this->blockColor));
		break;
	case eTetriminoShape::Bomb:
		this->points[0].setSymbol(BOMB_SYMBOL);
		generate3NonCenterPoints(Point(middleX, 2, BOMB_SYMBOL, this->blockColor), Point(middleX, 2, BOMB_SYMBOL, this->blockColor), Point(middleX, 2, BOMB_SYMBOL, this->blockColor));
		return;
	}

}

// Assuming that the points array property of the block first element is the "center" of the block
// It assigns the values of all 3 non "center" points.
void Block::generate3NonCenterPoints(const Point p1, const Point p2, const Point p3) {
	this->points[1] = p1;
	this->points[2] = p2;
	this->points[3] = p3;
}

// Takes the Block (assuming only NON I or O is assigned here) and makes it a 3x3 matrix so it will be easier to rotate
void Block::fromBlockToMatrix(char(&matrix)[3][3]) {
	int matrixElements = this->blockShape == eTetriminoShape::I ? 3 : 4;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			matrix[i][j] = EMPTY_SPACE;
		}
	}

	matrix[1][1] = this->points[0].getSymbol();
	int xDiffFromCenter, yDiffFromCenter;
	for (int i = 1; i < matrixElements; i++) {
		xDiffFromCenter = this->points[0].getX() - this->points[i].getX();
		yDiffFromCenter = this->points[0].getY() - this->points[i].getY();
		matrix[1 + xDiffFromCenter][1 + yDiffFromCenter] = this->points[0].getSymbol();
	}
}

// Takes a 3x3 matrix after rotation and makes it a block again while changing the values as it should.
void Block::fromMatrixToBlock(char(&matrix)[3][3]) {
	Point center = this->points[0];
	int pointsMoved = 0;
	int xDiffFromCenter;
	int yDiffFromCenter;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] == center.getSymbol() && (i != 1 || j != 1)) {
				xDiffFromCenter = i - 1;
				yDiffFromCenter = j - 1;
				this->points[pointsMoved + 1].setCoordinates(center.getX() + xDiffFromCenter, center.getY() + yDiffFromCenter);
				pointsMoved++;
			}
		}
	}
}

// Ensures that the last point of the I Tetrimino is correctly positioned after rotation
void Block::fixITetereminoLastPoint() {
	Point center = this->points[0];
	switch (this->rotateRightAmount) {
	case 1:
	case 3: 
		this->points[3] = Point(center.getX(), center.getY() + 2, center.getSymbol(), this->blockColor);
		break;
	case 2:
	case 0 :
		this->points[3] = Point(center.getX() - 2, center.getY(), center.getSymbol(), this->blockColor);
		break;
	}
}

// Moves the block to the relevant key.
// We can assume input is valid cause validated at Board class.
bool Block::moveBlock(GameConfig::eKeys key, bool shouldDraw) {
	for (int i = 0; i < 4; i++) {
		this->points[i].move(key, shouldDraw);
	}
	return true;
}

// Returns a random Tetrimino shape
Block::eTetriminoShape Block::getRandomShape() {
	return Block::eTetriminoShape::I;
	int randomValue = rand() % 100;
	if (randomValue >= 0 && randomValue < 5)
		return Block::eTetriminoShape::Bomb;
	else randomValue = rand() % 7;
	switch ((GameConfig::eKeys)randomValue) {
	case GameConfig::eKeys::ShapeO: return Block::eTetriminoShape::O;
	case GameConfig::eKeys::ShapeI: return Block::eTetriminoShape::I;
	case GameConfig::eKeys::ShapeT: return Block::eTetriminoShape::T;
	case GameConfig::eKeys::ShapeL: return Block::eTetriminoShape::L;
	case GameConfig::eKeys::ShapeJ: return Block::eTetriminoShape::J;
	case GameConfig::eKeys::ShapeS: return Block::eTetriminoShape::S;
	default: return Block::eTetriminoShape::Z;
	}
}

// Rotates all points in the block clockwise.
void Block::rotateClockwise() {
	if (this->blockShape == eTetriminoShape::O || this->isBomb)
		return;
	char matrix[3][3];
	// Call fromBlockToMatrix with the fixed-size matrix
	fromBlockToMatrix(matrix);
	rotateMatrixClockwise(matrix);
	fromMatrixToBlock(matrix);
	this->increaseRotateRightAmount();

	if (this->blockShape == eTetriminoShape::I) {
		fixITetereminoLastPoint();
	}
}

// Rotates the points at the block counter clockwise.
void Block::rotateCounterClockwise() {
	rotateClockwise();
	rotateClockwise();
	rotateClockwise();
}

// Function to rotate the matrix 90 degrees clockwise
void Block::rotateMatrixClockwise(char(&matrix)[3][3]) {
	int dimension = 3;
	// Traverse each cycle
	for (char i = 0; i < dimension / 2; i++) {
		for (char j = i; j < dimension - i - 1; j++) {
			// Swap elements of each cycle in clockwise direction
			char temp = matrix[i][j];
			matrix[i][j] = matrix[dimension - 1 - j][i];
			matrix[dimension - 1 - j][i] = matrix[dimension - 1 - i][dimension - 1 - j];
			matrix[dimension - 1 - i][dimension - 1 - j] = matrix[j][dimension - 1 - i];
			matrix[j][dimension - 1 - i] = temp;
		}
	}
}

// Increases the rotateRightAmount, ensuring it stays within the range [0, 3]
void Block::increaseRotateRightAmount() {
	this->rotateRightAmount++;
	if (this->rotateRightAmount == 4)
		this->rotateRightAmount = 0;
}

// Copies the properties of another block to this block
void Block::copyBlock(const Block& block) {
	for (int i = 0; i < 4; i++) {
		this->points[i].setCoordinates(block.points[i].getX(), block.points[i].getY(), true);
	}
	this->rotateRightAmount = block.rotateRightAmount;
	this->movedAmount = block.movedAmount;
}

// Draws the block by calling the draw method for each of its points
void Block::drawBlock() {
	for (int i = 0; i < 4; i++) {
		this->points[i].draw();
	}
}