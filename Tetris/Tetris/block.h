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
	char side;
	int rotateRightAmount;
	enum class eMoveDirection { ClockWise= 1, CounterClockWise= - 1 };

public:
	Block() = default;
	Block(eTetriminoShape shape, char side);
	void moveBlock(GameConfig::eKeys key, bool isNewBlock=false);
	void rotateClockwise();
	void rotateCounterClockwise();

private:
	void buildBlockPoints(char side);
	void generate3NonCenterPoints(Point p1, Point p2, Point p3);

	char** fromBlockToMatrix();
	void fromMatrixToBlock(char ** matrix);
	void rotateMatrixClockwise(char** matrix);
	void freeMatrix(char** matrix);
	void fixITetereminoLastPoint();
	void increaseRotateRightAmount();
	eTetriminoShape blockShape;
};
#endif