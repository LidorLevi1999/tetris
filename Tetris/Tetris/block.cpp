#include "block.h"
#include "Windows.h"
#include "gameConfig.h"
#include <iostream>
#include "general.h"
#include <array>

using namespace std;

//Constructor;
Block::Block(char side) {
	this->side = side;
	this->blockShape = getRandomShape();
	this->rotateRightAmount = 0;
	this->movedAmount = 0;
	buildBlockPoints();
}


//Build the 4 points of the block.
//Assume that a block is being created only at the middle top of the board.
void Block::buildBlockPoints() {
	int middleX = (GameConfig::BOARD_WIDTH + 1) / 2;
	if (this->side == 'R')
		middleX += GameConfig::RIVAL_POS;

	this->points[0] = Point(middleX, 2, '#');

	switch (this->blockShape) {
	case eTetriminoShape::O:
		generate3NonCenterPoints(Point(middleX + 1, 2, '#'), Point(middleX + 1, 1, '#'), Point(middleX , 1, '#'));
		break;
	case eTetriminoShape::T:
		generate3NonCenterPoints(Point(middleX - 1, 2, '#'), Point(middleX + 1, 2, '#'), Point(middleX, 1, '#'));
		break;
	case eTetriminoShape::L:
		generate3NonCenterPoints(Point(middleX - 1, 2, '#'), Point(middleX + 1, 2, '#'), Point(middleX + 1, 1, '#'));
		break;
	case eTetriminoShape::J:
		generate3NonCenterPoints(Point(middleX - 1, 1, '#'), Point(middleX - 1, 2, '#'), Point(middleX + 1, 2, '#'));
		break;
	case eTetriminoShape::S:
		generate3NonCenterPoints(Point(middleX - 1, 2, '#'), Point(middleX , 1, '#'), Point(middleX + 1, 1, '#'));
		break;
	case eTetriminoShape::Z:
		generate3NonCenterPoints(Point(middleX - 1, 1 , '#'), Point(middleX, 1, '#'), Point(middleX + 1, 2, '#'));
		break;
	case eTetriminoShape::I:
		this->points[0] = Point(middleX, 1, '#');
		generate3NonCenterPoints(Point(middleX - 1, 1, '#'), Point(middleX + 1, 1, '#'), Point(middleX + 2, 1, '#'));
		break;
	}
}


//Assuming that the points array property of the block first element is the "center" of the block
//It assign the values of all 3 non "center" points.
void Block::generate3NonCenterPoints(Point p1, Point p2, Point p3) {
	this->points[1] = p1;
	this->points[2] = p2;
	this->points[3] = p3;
}


//Takes the Block(assuming only NON I or O is assigned here) and makes it a 3x3 matrix so it will be easier to rotate
char ** Block::fromBlockToMatrix() {
	int matrixElements = this->blockShape == eTetriminoShape::I ? 3 : 4;
	char** matrix = buildCharMatrix(3);
	matrix[1][1] = this->points[0].getSymbol();
	int xDiffFromCenter, yDiffFromCenter;
	for (int i = 1; i < matrixElements; i++) {
		xDiffFromCenter = this->points[0].getX() - this->points[i].getX();
		yDiffFromCenter = this->points[0].getY() - this->points[i].getY();
		matrix[1 + xDiffFromCenter][1 + yDiffFromCenter] = this->points[0].getSymbol();
	}
	return matrix;
}


//Takes a 3x3 matrix after rotation and makes it a block again while changing the values as it should.
//TODO : remove matrixDimension.
void Block::fromMatrixToBlock(char** matrix) {
	Point center = this->points[0];
	int pointsMoved = 0;
	int xDiffFromCenter;
	int yDiffFromCenter;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] == center.getSymbol() && (i != 1 || j != 1)) {
				xDiffFromCenter = i - 1;
				yDiffFromCenter = j - 1;
				//this->points[pointsMoved + 1] = Point(center.getX() + xDiffFromCenter, center.getY() + yDiffFromCenter, center.getSymbol());
				this->points[pointsMoved + 1].setCoordinates(center.getX() + xDiffFromCenter, center.getY() + yDiffFromCenter);
				pointsMoved++;
			}
		}
	}
	freeMatrix(matrix);
}


void Block::fixITetereminoLastPoint() {
	Point center = this->points[0];
	switch (this->rotateRightAmount) {
	case 1:
	case 3: 
		this->points[3] = Point(center.getX(), center.getY() + 2, center.getSymbol());
		break;
	case 2:
	case 0 :
		this->points[3] = Point(center.getX() - 2, center.getY(), center.getSymbol());
		break;
	}
}


//Free all arrays in the matrix
//TODO : remove size ?
void Block::freeMatrix(char** matrix) {
	for (int i = 0; i < 3; i++) {
		delete matrix[i];
	}
	delete matrix;
}


//Moves the block to the relevant key.
//We can assume input is valid cause validated at Board class.
bool Block::moveBlock(GameConfig::eKeys key, bool shouldDraw) {
	for (int i = 0; i < 4; i++) {
		this->points[i].move(key, shouldDraw);
	}
	return true;
}


Block::eTetriminoShape Block::getRandomShape() {
	return Block::eTetriminoShape::I;

	int randomValue = rand() % 7;
	switch (randomValue) {
	case 0: return Block::eTetriminoShape::O;
	case 1: return Block::eTetriminoShape::I;
	case 2: return Block::eTetriminoShape::T;
	case 3: return Block::eTetriminoShape::L;
	case 4: return Block::eTetriminoShape::J;
	case 5: return Block::eTetriminoShape::S;
	default: return Block::eTetriminoShape::Z;
	}
}


//Rotates all points in the block clockwise.
void Block::rotateClockwise() {
	if (this->blockShape == eTetriminoShape::O)
		return;
	char** matrix = fromBlockToMatrix();
	rotateMatrixClockwise(matrix);
	fromMatrixToBlock(matrix);
	this->increaseRotateRightAmount();

	if (this->blockShape == eTetriminoShape::I) {
		fixITetereminoLastPoint();
	}
}


//Rotates the points at the block counter clockwise.
void Block::rotateCounterClockwise() {
	rotateClockwise();
	rotateClockwise();
	rotateClockwise();
}


// Function to rotate the matrix 90 degree clockwise
void Block::rotateMatrixClockwise(char** matrix){
	int dimension = 3;
	// Traverse each cycle
	for (char i = 0; i < dimension / 2; i++) {
		for (char j = i; j < dimension - i - 1; j++) {
			// Swap elements of each cycle
			// in clockwise direction
			char temp = matrix[i][j];
			matrix[i][j] = matrix[dimension - 1 - j][i];
			matrix[dimension - 1 - j][i] = matrix[dimension - 1 - i][dimension - 1 - j];
			matrix[dimension - 1 - i][dimension - 1 - j] = matrix[j][dimension - 1 - i];
			matrix[j][dimension - 1 - i] = temp;
		}
	}
}


void Block::increaseRotateRightAmount() {
	this->rotateRightAmount++;
	if (this->rotateRightAmount == 4)
		this->rotateRightAmount = 0;
}


void Block::copyBlock(Block& block) {
	for (int i = 0; i < 4; i++) {
		this->points[i].setCoordinates(block.points[i].getX(), block.points[i].getY(), true);
	}
	this->rotateRightAmount = block.rotateRightAmount;
	this->movedAmount = block.movedAmount;
}


void Block::drawBlock() {
	for (int i = 0; i < 4; i++) {
		this->points[i].draw(GameConfig::COLORS[0]);
	}
}