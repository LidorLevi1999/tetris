#ifndef __GAME_H
#define __GAME_H

#include "user.h"
class GameManager 
{
	User LUser;
	User RUser;
	
public:
	GameManager() : LUser('L'), RUser('R') {};
	void startGame();
	void showMenu();
	void gamePaused();
	void gameResumed();
};

#endif