#include "game.h"
#include <iostream>
#include <windows.h>
#include <conio.h> 
#include "block.h"
#include "board.h"
#include <ctime>
#include <cstdlib>

void Game::startGame() {
	Board leftBoard, rightBoard;
	leftBoard.drawBoard('L');
	rightBoard.drawBoard('R');

	bool leftBlockMoved = false;
	bool rightBlockMoved = false;

	srand((time(nullptr)));

	Block leftBlock('L');
	Block rightBlock('R');

	leftBlock.moveBlock(GameConfig::eKeys::DROPP1, true);
	rightBlock.moveBlock(GameConfig::eKeys::DROPP2, true);

	Sleep(1500);

	while (true)
	{
		if (_kbhit()) {
			char pressedChar = _getch();

			leftBlockMoved = false;
			rightBlockMoved = false;

			switch ((GameConfig::eKeys)pressedChar) {
			//Left cases
			case GameConfig::eKeys::LEFTP1:
				leftBlock.moveBlock(GameConfig::eKeys::LEFTP1);
				break;
			case GameConfig::eKeys::LEFTP2:
				rightBlock.moveBlock(GameConfig::eKeys::LEFTP2);
				break;

			//Right cases
			case GameConfig::eKeys::RIGHTP1:
				leftBlock.moveBlock(GameConfig::eKeys::RIGHTP1);
				break;
			case GameConfig::eKeys::RIGHTP2:
				rightBlock.moveBlock(GameConfig::eKeys::RIGHTP2);
				break;

			//Drop cases
			case GameConfig::eKeys::DROPP1:
				leftBlockMoved = leftBlock.moveBlock(GameConfig::eKeys::DROPP1);
				break;
			case GameConfig::eKeys::DROPP2:
				rightBlockMoved = rightBlock.moveBlock(GameConfig::eKeys::DROPP2);
				break;

			// Rotate Clockwise cases
			case GameConfig::eKeys::ROTATE_CLOCKP1:
				leftBlock.rotateClockwise();
				break;
			case GameConfig::eKeys::ROTATE_CLOCKP2:
				rightBlock.rotateClockwise();
				break;

			// Rotate Counter Clockwise cases
			case GameConfig::eKeys::ROTATE_COUNTERP1:
				leftBlock.rotateCounterClockwise();
				break;
			case GameConfig::eKeys::ROTATE_COUNTERP2:
				rightBlock.rotateCounterClockwise();
				break;
			}
		}

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

		leftBlockMoved = leftBlock.moveBlock(GameConfig::eKeys::DROPP1);
		rightBlockMoved = rightBlock.moveBlock(GameConfig::eKeys::DROPP2);

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

		Sleep(500);
	}
}

void Game::showMenu() {

}

void Game::gamePaused() {

}

void Game::gameResumed() {

}