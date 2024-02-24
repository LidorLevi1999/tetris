// Header file for the ComputerUser class.

#ifndef __COMPUTER_USER_H
#define __COMPUTER_USER_H

#include "user.h"
#include <vector>
#include "game.h" ////////////// DELETE

class ComputerUser : public User
{
	const GameConfig::eKeys leftMove;
	const GameConfig::eKeys rightMove;
	const GameConfig::eKeys downMove;
	const GameConfig::eKeys rotateClockwise;
	const GameConfig::eKeys rotateCounterClockwise;
	int level;
	int numOfMove;

	std::vector<GameConfig::eKeys> bestMovement;

	// Creates a new moving block and calculates the best movement sequence for it.
	void createNewMovingBlock() override;

	// Calculates the best movement sequence for the current moving block.
	void calculateBestMovement();

	// Gets the amount of points at the given Y coordinate on the board.
	int getAmountOfPointsAtY(Board& b, const int y);

	// Gets the lowest Y coordinate of the given block.
	int getLowestY(const Block& b);

	// Gets the highest Y coordinate of the given block and how much there are.
	int getNumOfLowestY(const Block& b, int* numOfLowest);

	// Gets the highest Y coordinate of the given block.
	int getHighestY(const Block& b);

	// Gets the lowest Y coordinate of the given block and how much there are.
	int getNumOfHighestY(const Block& b, int* numOfHighest);

	// Finds all movements with the best score.
	std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allBestScoreMovement(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements);

	// Gets the distance of the given block from the left border.
	int getBlockDistanceFromLeftBorder(const Block& myBlock);

	// Gets the distance of the given block from the right border.
	int getBlockDistanceFromRightBorder(const Block& myBlock);

	// Gets the total amount of points above the given Y coordinate on the board.
	int getAmountOfPointsAboveY(Board& b, const int y);

	// Finds all possible movements for the current moving block.
	std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> findAllPossibleMovements();

	// Finds all movements with the most downward points.
	std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allMostPointsDownMovements(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements);

	// Finds all movements with the most downward points.
	std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allLeastPointsUpMovements(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements);

	// Finds all movements with the most left moves.
	std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allMostLeftMovements(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements);

public:
	// Constructor
	ComputerUser(char side, int level) :
		User(side),
		leftMove(side == 'L' ? GameConfig::eKeys::LEFTP1 : GameConfig::eKeys::LEFTP2),
		rightMove(side == 'L' ? GameConfig::eKeys::RIGHTP1 : GameConfig::eKeys::RIGHTP2),
		rotateClockwise(side == 'L' ? GameConfig::eKeys::ROTATE_CLOCKP1 : GameConfig::eKeys::ROTATE_CLOCKP2),
		rotateCounterClockwise(side == 'L' ? GameConfig::eKeys::ROTATE_COUNTERP1 : GameConfig::eKeys::ROTATE_COUNTERP2),
		downMove(side == 'L' ? GameConfig::eKeys::DROPP1 : GameConfig::eKeys::DROPP2)
	{
		this->level = level;
		this->numOfMove = 0;
		createNewMovingBlock();
		resetScore();
		resetBoard();
	};

	// Handles the movement of the current block.
	virtual void handleMovement(GameConfig::eKeys direction = GameConfig::eKeys::NONE) override;
};

#endif