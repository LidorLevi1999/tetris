#pragma once
#ifndef __BLOCK_H
#define __BLOCK_H
#include "point.h"

class Block
{
public:
		enum class eTetriminoShape { O, I, T, L, J, S, Z };
private:
	Point points[4];
	int rotateRightAmount;
	enum class eMoveDirection { ClockWise= 1, CounterClockWise= - 1 };

public:
	Block() = default;
	Block(eTetriminoShape shape);
	void moveBlock(GameConfig::eKeys key);
	void rotateClockwise();
	void rotateCounterClockwise();

private:
	void buildBlockPoints();
	void genetrate3NonCenterPoints(Point p1, Point p2, Point p3);

	char** fromBlockToMatrix();
	void fromMatrixToBlock(char ** matrix, int matrixDimension);
	void rotateMatrixClockwise(char** matrix, int Dimension);
	void freeMatrix(char** matrix, int Dimension);
	void rotateITetremino();
	bool ITetreminoBlockOnSameX();

	eTetriminoShape blockShape;
};
#endif