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
	int showMenu();
	void gamePause();
	void gameResume();
	void showInstructions();
	void gameRestart();
	void gameEnd();
};

#endif