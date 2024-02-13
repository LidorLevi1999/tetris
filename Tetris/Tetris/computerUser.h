// Header file for the ComputerUser class.

#ifndef __COMPUTER_USER_H
#define __COMPUTER_USER_H

#include "user.h"
#include <vector>

class ComputerUser : public User
{
	const GameConfig::eKeys leftMove;
	const GameConfig::eKeys rightMove;
	const GameConfig::eKeys downMove;
	const GameConfig::eKeys rotateClockwise;
	const GameConfig::eKeys rotateCounterClockwise;
private:
	std::vector<GameConfig::eKeys> bestMovement;
	void createNewMovingBlock() override;
	void calculateBestMovement();
	int calculateMovingBlockDistanceFromLeftBorder();
	std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> findAllPossibleMovements();
	void exploreAllPossibleMoves(Block& block, std::vector<GameConfig::eKeys>& moves, std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allMoves);
	std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allBestScoreMovement(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements);
	std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allMostPointsDownMovements(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements);
	std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allLeastPointsUpMovments(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements);
	int getLowestY(const Block& b);
	int getHighestY(const Block& b);
	int getAmountOfPointsAtY(Board& b,const int y);
public:
	// Constructor
	ComputerUser(char side) :
		User(side),
		leftMove(side == 'L' ? GameConfig::eKeys::LEFTP1 : GameConfig::eKeys::LEFTP2),
		rightMove(side == 'L' ? GameConfig::eKeys::RIGHTP1 : GameConfig::eKeys::RIGHTP2),
		rotateClockwise(side == 'L' ? GameConfig::eKeys::ROTATE_CLOCKP1 : GameConfig::eKeys::ROTATE_CLOCKP2),
		rotateCounterClockwise(side == 'L' ? GameConfig::eKeys::ROTATE_COUNTERP1 : GameConfig::eKeys::ROTATE_COUNTERP2),
		downMove(side == 'L' ? GameConfig::eKeys::DROPP1 : GameConfig::eKeys::DROPP2) 
	{ 
		createNewMovingBlock();
		resetScore();
		resetBoard();
	};

	virtual void handleMovement(GameConfig::eKeys direction = GameConfig::eKeys::NONE);
};

#endif