#include "game.h"
#include <iostream>
#include <windows.h>
#include <conio.h> 
#include "block.h"
//#include "board.h"
#include "user.h"
#include <ctime>
#include <cstdlib>


void GameManager::startGame() {
	bool leftBlockMoved = false;
	bool rightBlockMoved = false;

	srand((time(nullptr)));

	//this->LUser.board.updateBoardWithPoints(this->LUser.movingBlock.getBlockPoints());
	//this->RUser.board.updateBoardWithPoints(this->RUser.movingBlock.getBlockPoints());
	//this->LUser.movingBlock.moveBlock(GameConfig::eKeys::DROPP1);
	//this->RUser.movingBlock.moveBlock(GameConfig::eKeys::DROPP2);

	Sleep(1000);

	while (true)
	{
		if (_kbhit()) {
			char pressedChar = _getch();

			leftBlockMoved = false;
			rightBlockMoved = false;
			switch ((GameConfig::eKeys)pressedChar) {
			//Left cases
			case GameConfig::eKeys::LEFTP1:
				this->LUser.moveMovingBlock(GameConfig::eKeys::LEFTP1);
				break;
			case GameConfig::eKeys::LEFTP2:
				this->RUser.moveMovingBlock(GameConfig::eKeys::LEFTP2);
				break;

			//Right cases
			case GameConfig::eKeys::RIGHTP1:
				this->LUser.moveMovingBlock(GameConfig::eKeys::RIGHTP1);
				break;
			case GameConfig::eKeys::RIGHTP2:
				this->RUser.moveMovingBlock(GameConfig::eKeys::RIGHTP2);
				break;

			//Drop cases
			case GameConfig::eKeys::DROPP1:
				this->LUser.moveMovingBlock(GameConfig::eKeys::DROPP1);
				break;
			case GameConfig::eKeys::DROPP2:
				this->RUser.moveMovingBlock(GameConfig::eKeys::DROPP2);
				break;

			// Rotate Clockwise cases
			case GameConfig::eKeys::ROTATE_CLOCKP1:
				this->LUser.rotateMovingBlock();
				break;
			case GameConfig::eKeys::ROTATE_CLOCKP2:
				this->RUser.rotateMovingBlock();
				break;

			// Rotate Counter Clockwise cases
			case GameConfig::eKeys::ROTATE_COUNTERP1:
				this->LUser.rotateMovingBlock(false);
				break;
			case GameConfig::eKeys::ROTATE_COUNTERP2:
				this->RUser.rotateMovingBlock(false);
				break;
			}
		}

/*
		// IT CHECKS TWICE BECAUSE ITS POSSIBLE THAT IN THE WHILE LOOP YOU PRESSED
		// DROP AND THEN IT NEED TO CHECK IF YOU'RE STUCK OR NOT
		// TODO -- THINK HOW TO DO IT ONLY ONCE AND NOT TWICE BECAUSE IT'S DUPLICATED

		// Checks if a block couldn't move, make it static and create new block
		if (!leftBlockMoved) {
			// TODO - Make Block Static
			// leftBlock.makeBlockStatic();
			// TODO - Random Shape Generator
			// leftBlock = newBlockGenerator('L');
		}
		if (!rightBlockMoved) {
			// TODO - Make Block Static
			// rightBlock.makeBlockStatic();
			// TODO - Random Shape Generator
			// rightBlock = newBlockGenerator('R');
		}
*/
		leftBlockMoved = this->LUser.moveMovingBlock(GameConfig::eKeys::DROPP1);
		rightBlockMoved = this->RUser.moveMovingBlock(GameConfig::eKeys::DROPP2);

		// Checks if a block couldn't move, make it static and create new block
		if (!leftBlockMoved) {
			if (this->LUser.getMovingBlock().getMovedAmount() == 0)
				return;
			this->LUser.updateBoardAndAssignGenerateNewBlock();
			// TODO - Make Block Static
			// leftBlock.makeBlockStatic();
			// TODO - Random Shape Generator
			// leftBlock = newBlockGenerator('L');
		}
		if (!rightBlockMoved) {
			this->RUser.updateBoardAndAssignGenerateNewBlock();
			// TODO - Make Block Static
			// rightBlock.makeBlockStatic();
			// TODO - Random Shape Generator
			// rightBlock = newBlockGenerator('R');
		}

		Sleep(1000);
	}
}

void GameManager::showMenu() {

}

void GameManager::gamePaused() {

}

void GameManager::gameResumed() {

}