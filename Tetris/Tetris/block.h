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
	int movedAmount;
	eTetriminoShape blockShape;
	int blockColor;

public:
	Block() = default;
	Block(char side);
	bool moveBlock(GameConfig::eKeys key, bool shouldDraw = false);
	void rotateClockwise();
	void rotateCounterClockwise();
	char getSide() const { return this->side; };
	Point* getBlockPoints() { return this->points; };
	void copyBlock(Block& block);
	void drawBlock();
	int getMovedAmount() const { return this->movedAmount; };
	void increaseMoveAmount() { this->movedAmount++; };
private:
	void buildBlockPoints();
	void generate3NonCenterPoints(Point p1, Point p2, Point p3);
	char** fromBlockToMatrix();
	void fromMatrixToBlock(char ** matrix);
	void rotateMatrixClockwise(char** matrix);
	void freeMatrix(char** matrix);
	void fixITetereminoLastPoint();
	void increaseRotateRightAmount();
	eTetriminoShape getRandomShape();
};
#endif