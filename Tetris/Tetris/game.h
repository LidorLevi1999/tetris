#ifndef __GAME_H
#define __GAME_H

#include "board.h"

class Game 
{
	Board leftBoard;
	Board rightBoard;
	
public:
	void startGame();
	void showMenu();
	void gamePaused();
	void gameResumed();
};

#endif