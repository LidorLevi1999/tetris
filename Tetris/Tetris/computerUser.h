// Header file for the ComputerUser class.

#ifndef __COMPUTER_USER_H
#define __COMPUTER_USER_H

#include "user.h"

class ComputerUser : public User
{

public:
	// Constructor
	ComputerUser(char side) : User(side) {};

	// Move the current moving block based on user input
	virtual bool moveMovingBlock(GameConfig::eKeys direction);

	// Rotate the current moving block
	virtual bool rotateMovingBlock(bool clockWise = true);

};

#endif