#include "block.h"
#include "Windows.h"
#include "gameConfig.h"
#include <iostream>
#include "general.h"
#include <array>

using namespace std;
void rotateMatrixClockwise(char** matrix, int Dimension);

//Constructor;
Block::Block(eTetriminoShape shape) {
	this->blockShape = shape;
	this->rotateRightAmount = 0;
	buildBlockPoints();
}

//Build the 4 points of the block.
//Assume that a block is being created only at the middle top of the board.
void Block::buildBlockPoints() {
	int middleX = (GameConfig::GAME_WIDTH + 1) / 2;
	this->points[0] = Point(middleX, 2, '#');

	switch (this->blockShape) {
	case eTetriminoShape::O:
		genetrate3NonCenterPoints(Point(middleX, 1 , '#'), Point(middleX+1,1,'#'), Point(middleX+1,2,'#'));
		break;
	case eTetriminoShape::T:
		genetrate3NonCenterPoints(Point(middleX, 1 , '#'), Point(middleX - 1, 2, '#'), Point(middleX + 1, 2, '#'));
		break;
	case eTetriminoShape::L:
		genetrate3NonCenterPoints(Point(middleX -1 , 2, '#'), Point(middleX + 1, 2, '#'), Point(middleX + 1, 1, '#'));
		break;
	case eTetriminoShape::J:
		genetrate3NonCenterPoints(Point(middleX + 1 , 2, '#'), Point(middleX - 1, 2, '#'), Point(middleX - 1, 1, '#'));
		break;
	case eTetriminoShape::S:
		genetrate3NonCenterPoints(Point(middleX - 1 , 2, '#'), Point(middleX, 1, '#'), Point(middleX + 1, 1, '#'));
		break;
	case eTetriminoShape::Z:
		genetrate3NonCenterPoints(Point(middleX - 1 , 1, '#'), Point(middleX, 1, '#'), Point(middleX + 1, 2, '#'));
		break;
	case eTetriminoShape::I:
		genetrate3NonCenterPoints(Point(middleX - 2 , 2, '#'), Point(middleX - 1, 2, '#'), Point(middleX + 1, 2, '#'));
		break;
	}
}

//Assuming that the points array property of the block first element is the "center" of the block
//It assign the values of all 3 non "center" points.
void Block::genetrate3NonCenterPoints(Point p1, Point p2, Point p3) {
	this->points[1] = p1;
	this->points[2] = p2;
	this->points[3] = p3;
}


//Takes the Block(assuming only NON I or O is assigned here) and makes it a 3x3 matrix so it will be easier to rotate
char ** Block::fromBlockToMatrix() {
	char** matrix = buildCharMatrix(3);
	matrix[1][1] = this->points[0].getSymbol();
	int xDiffFromCenter, yDiffFromCenter;
	for (int i = 1; i < 4; i++) {
		xDiffFromCenter = this->points[0].getX() - this->points[i].getX();
		yDiffFromCenter = this->points[0].getY() - this->points[i].getY();
		matrix[1 + xDiffFromCenter][1 + yDiffFromCenter] = this->points[0].getSymbol();
	}
	return matrix;
}


//Rotates I Tetremino as its a different logic for rotation.
void Block::rotateITetremino() {
	Point center = this->points[0];
	array<int, 4> xOffset = { 1, 0, -1, 0 };
	array<int, 4> yOffset = { 0, 1, 0, -1 };
	int pointsMoved = 0;  // Start from the first point
	this->rotateRightAmount++;
	if (this->rotateRightAmount > 3)
		this->rotateRightAmount -= 4;
	if (this->ITetreminoBlockOnSameX()) {
		this->points[1] = Point(center.getX() + ((this->rotateRightAmount == 2) ? -2 : 2), center.getY(), center.getSymbol());
		this->points[2] = center;
		this->points[3] = Point(center.getX() + ((this->rotateRightAmount == 2) ? 1 : -1), center.getY(), center.getSymbol());
	}
	else {
		this->points[1] = Point(center.getX(), center.getY() + ((this->rotateRightAmount == 1) ? - 1 : -2), center.getSymbol());
		this->points[2] = center;
		this->points[3] = Point(center.getX(), center.getY() + ((this->rotateRightAmount == 1) ? 2 : 1) , center.getSymbol());
	}
	this->points[0] = Point(center.getX() + xOffset[this->rotateRightAmount], center.getY() + yOffset[this->rotateRightAmount], center.getSymbol());
}


//Checks if the I teteremino is parallel to x axis
bool Block::ITetreminoBlockOnSameX() {
	int x = this->points[0].getX();
	for (int i = 1; i < 4; i++) {
		if (this->points[i].getX() != x)
			return false;
	}
	return true;
}


//Takes a 3x3 matrix after rotation and makes it a block again while changing the values as it should.
//TODO : remove matrixDimension.
void Block::fromMatrixToBlock(char** matrix, int matrixDimension) {
	Point center = this->points[0];
	int pointsMoved = 0;
	int xDiffFromCenter;
	int yDiffFromCenter;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] == center.getSymbol() && (i != 1 || j != 1)) {
				xDiffFromCenter = i - 1;
				yDiffFromCenter = j - 1;
				this->points[pointsMoved + 1] = Point(center.getX() + xDiffFromCenter, center.getY() + yDiffFromCenter, center.getSymbol());
				pointsMoved++;
			}
		}
	}
	freeMatrix(matrix, matrixDimension);
}


//Free all arrays in the matrix
//TODO : remove size ?
void Block::freeMatrix(char** matrix, int size) {
	for (int i = 0; i < size; i++) {
		delete matrix[i];
	}
	delete matrix;
}


//Moves the block to the relevant key.
//We can assume input is valid cause validated at Board class.
void Block::moveBlock(GameConfig::eKeys key) {
	for (int i = 0; i < 4; i++) {
		this->points[i].move(key);
	}
}

//Rotates all points in the block clockwise.
void Block::rotateClockwise() {
	if (this->blockShape == eTetriminoShape::O)
		return;
	int matrixDimension = this->blockShape == Block::eTetriminoShape::I ? 4 : 3;
	if (matrixDimension == 3) {
		char** matrix = fromBlockToMatrix();
		fromMatrixToBlock(matrix, matrixDimension);
		rotateMatrixClockwise(matrix, matrixDimension);
	}
	else rotateITetremino();

}


//Rotates the points at the block counter clockwise.
void Block::rotateCounterClockwise() {
	rotateClockwise();
	rotateClockwise();
	rotateClockwise();
}


// Function to rotate the matrix 90 degree clockwise
void Block::rotateMatrixClockwise(char** matrix, int Dimension){
	// Traverse each cycle
	for (char i = 0; i < Dimension / 2; i++) {
		for (char j = i; j < Dimension - i - 1; j++) {
			// Swap elements of each cycle
			// in clockwise direction
			char temp = matrix[i][j];
			matrix[i][j] = matrix[Dimension - 1 - j][i];
			matrix[Dimension - 1 - j][i] = matrix[Dimension - 1 - i][Dimension - 1 - j];
			matrix[Dimension - 1 - i][Dimension - 1 - j] = matrix[j][Dimension - 1 - i];
			matrix[j][Dimension - 1 - i] = temp;
		}
	}
}
