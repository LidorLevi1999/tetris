#ifndef __GAME_H
#define __GAME_H

#include "user.h"
class GameManager 
{
	User LUser;
	User RUser;
	bool isGameRunning;
	bool isGameSupportColors;
public:
	GameManager() : LUser('L'), RUser('R') { this->isGameRunning = false;  this->isGameSupportColors = false; };
	void startGame();
	int showMenu();
	void showInstructions();
	void playGame();
	void drawBoards();
	void drawScore(); 
	void updateScoreTable();
	void declareWinner();
};

#endif