// Implementation file for the User class.


#include "humanUser.h"
#include "gameConfig.h"


void HumanUser::handleMovement(GameConfig::eKeys direction) {
	switch ((GameConfig::eKeys)direction) {
		// Left player controls
	case GameConfig::eKeys::LEFTP1:
	case GameConfig::eKeys::RIGHTP1:
	case GameConfig::eKeys::DROPP1:
		if (this->getSide() == 'L')
			this->moveMovingBlock((GameConfig::eKeys)direction);
		break;
	case GameConfig::eKeys::ROTATE_CLOCKP1:
	case GameConfig::eKeys::ROTATE_COUNTERP1:
		if (this->getSide() == 'L')
			this->rotateMovingBlock((GameConfig::eKeys)direction == GameConfig::eKeys::ROTATE_CLOCKP1);
		break;

		// Right player controlsbut 
	case GameConfig::eKeys::LEFTP2:
	case GameConfig::eKeys::RIGHTP2:
	case GameConfig::eKeys::DROPP2:
		if (this->getSide() == 'R')
			this->moveMovingBlock((GameConfig::eKeys)direction);
		break;
	case GameConfig::eKeys::ROTATE_CLOCKP2:
	case GameConfig::eKeys::ROTATE_COUNTERP2:
		if (this->getSide() == 'R')
			this->rotateMovingBlock((GameConfig::eKeys)direction == GameConfig::eKeys::ROTATE_CLOCKP2);
		break;
	}
}

