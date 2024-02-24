// Header file for the HumanUser class.

#ifndef __HUMAN_USER_H
#define __HUMAN_USER_H

#include "user.h"

class HumanUser : public User
{
public:
	// Constructor
	HumanUser(char side) : User(side) { 
		createNewMovingBlock();
		resetBoard();
		resetScore();
	};

	// Handles the movement of the current block.
	virtual void handleMovement(GameConfig::eKeys direction = GameConfig::eKeys::NONE) override;
};

#endif