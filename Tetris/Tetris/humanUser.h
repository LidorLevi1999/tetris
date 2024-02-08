// Header file for the HumanUser class.

#ifndef __HUMAN_USER_H
#define __HUMAN_USER_H

#include "user.h"

class HumanUser : public User
{

public:
	// Constructor
	HumanUser(char side) : User(side) {};

	// Move the current moving block based on user input
	virtual bool moveMovingBlock(GameConfig::eKeys direction);

	// Rotate the current moving block
	virtual bool rotateMovingBlock(bool clockWise = true);

};

#endif