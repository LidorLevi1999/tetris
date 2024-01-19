#include "game.h"
#include <iostream>
#include <windows.h>
#include <conio.h> 
#include "block.h"
//#include "board.h"
#include "user.h"
#include <ctime>
#include <cstdlib>

using namespace std;

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

			// User paused
			case GameConfig::eKeys::ESC:
				gamePause();
			}
		}

		leftBlockMoved = this->LUser.moveMovingBlock(GameConfig::eKeys::DROPP1);
		rightBlockMoved = this->RUser.moveMovingBlock(GameConfig::eKeys::DROPP2);

		// Checks if a block couldn't move, make it static and create new block
		if (!leftBlockMoved && !rightBlockMoved) {
			if (this->LUser.getMovingBlock().getMovedAmount() == 0 || this->RUser.getMovingBlock().getMovedAmount() == 0)
				return;
			//TIE
		}
		if (!leftBlockMoved) {
			if (this->LUser.getMovingBlock().getMovedAmount() == 0)
				return;
			this->LUser.updateBoardAndAssignGenerateNewBlock();
		}
		if (!rightBlockMoved) {
			if (this->RUser.getMovingBlock().getMovedAmount() == 0)
				return;
			this->RUser.updateBoardAndAssignGenerateNewBlock();
		}

		Sleep(800);
	}
}

int GameManager::showMenu() {
	while (true) {
		system("cls");
		cout << "The game has been paused, make your choice using the keyboard:" << endl;
		cout << "(1) Start a new game" << endl;
		cout << "(2) Continue a paused game" << endl;
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl;

		char pressedChar = _getch();

		switch ((int)pressedChar) {
		case '1':
			system("cls");
			cout << "A new game will be started in 3 seconds.." << endl;
			Sleep(3000);
			return 2;
		case '2':
			system("cls");
			cout << "The game will be resumed in 3 seconds.." << endl;
			Sleep(3000);
			return 1;
		case '8':
			system("cls");
			showInstructions();
			Sleep(3000);
			break;
		case '9':
			system("cls");
			cout << "The game will exit in 3 seconds.." << endl;
			Sleep(3000);
			break;
		default:
			cout << "Invalid selection. Please try again." << endl;
			Sleep(1000);
			break;
		}
	}
}

void GameManager::gamePause() {
	switch (showMenu()) {
	case 1:
		gameResume();
		return;
	case 2:
		gameRestart();
		return;
	case 3:
		gameEnd();
		return;
	}
}

void GameManager::showInstructions() {
	// Brief explanation of Tetris
	cout << "Hello and welcome to Lidor & Bar Tetris game!" << std::endl;
	cout << "Tetris is a puzzle game where you must fit falling blocks into a line at the bottom of the playing board." << endl;
	cout << "Completing a line clears it and earns points, the game ends when the blocks reach the top of the board." << endl << endl;

	// Instructions for the game controls
	cout << "Here are the controls for the game:" << endl << endl;

	// Instructions for the left player
	cout << "Left Player Controls:" << endl;
	cout << "Move Left: Press 'a' or 'A'" << endl;
	cout << "Move Right: Press 'd' or 'D'" << endl;
	cout << "Rotate Clockwise: Press 's' or 'S'" << endl;
	cout << "Rotate Counterclockwise: Press 'w' or 'W'" << endl;
	cout << "Drop: Press 'x' or 'X'" << endl << endl;

	// Instructions for the right player
	cout << "Right Player Controls:" << endl;
	cout << "Move Left: Press 'j' or 'J'" << endl;
	cout << "Move Right: Press 'l' or 'L'" << endl;
	cout << "Rotate Clockwise: Press 'k' or 'K'" << endl;
	cout << "Rotate Counterclockwise: Press 'i' or 'I'" << endl;
	cout << "Drop: Press 'm' or 'M'" << endl << endl;

	// Instruction how to return to main menu
	cout << "Press ESC key to return." << endl << endl;

	while (true) {
		if ((GameConfig::eKeys)_getch() == GameConfig::eKeys::ESC)
			return;
		else
		{
			cout << "Invalid selection. Please try again." << endl;
			Sleep(1000);
		}
	}
}

void GameManager::gameResume() {
	// Print the board, the main loop will keep running
}

void GameManager::gameRestart() {
	// Free everything, create new boards, reset scores, the main loop will keep running
}

void GameManager::gameEnd() {
	// Free everything, and then exit(0)
}