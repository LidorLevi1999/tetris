// Header file for the Block class.

#ifndef __BLOCK_H
#define __BLOCK_H
#include "point.h"

class Block
{
public:
    // Enum representing different Tetrimino shapes
    enum class eTetriminoShape { O, I, T, L, J, S, Z };

private:
	Point points[4];
	char side;
	int rotateRightAmount;
	int movedAmount;
	eTetriminoShape blockShape;
    int blockColor;

public:
    // Default constructor
    Block() = default;

    // Parameterized constructor
    Block(char side);

    // Move the block in the specified direction
    bool moveBlock(GameConfig::eKeys key, bool shouldDraw = false);

    // Rotate the block clockwise
    void rotateClockwise();

    // Rotate the block counter-clockwise
    void rotateCounterClockwise();

    // Get the side of the block
    char getSide() const { return this->side; };

    // Get the points of the block
    Point* getBlockPoints() { return this->points; };

    // Copy properties from another block
    void copyBlock(Block& block);

    // Draw the block on the screen
    void drawBlock();

    // Get the number of times the block has been moved
    int getMovedAmount() const { return this->movedAmount; };

    // Increase the count of moved times
    void increaseMoveAmount() { this->movedAmount++; };

private:
    // Build the 4 points of the block based on its shape
    void buildBlockPoints();

    // Generate 3 non-center points for the block
    void generate3NonCenterPoints(Point p1, Point p2, Point p3);

    // Convert the block to a 3x3 matrix for easier rotation
    void fromBlockToMatrix(char matrix[3][3]);

    // Convert a 3x3 matrix after rotation back to a block
    void fromMatrixToBlock(char matrix[3][3]);

    // Rotate the matrix 90 degrees clockwise
    void rotateMatrixClockwise(char matrix[3][3]);

    // Free the dynamically allocated memory for a matrix
    void freeMatrix(char** matrix);

    // Fix the position of the last point for the I Tetrimino after rotation
    void fixITetereminoLastPoint();

    // Increase the count of right rotations
    void increaseRotateRightAmount();

    // Get a random Tetrimino shape
    eTetriminoShape getRandomShape();
};
#endif