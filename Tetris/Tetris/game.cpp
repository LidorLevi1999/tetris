#include "game.h"
#include <iostream>
#include <windows.h>
#include <conio.h> 
#include "block.h"
//#include "board.h"
#include "user.h"
#include <ctime>
#include <cstdlib>
#include "general.h"
#include "gameConfig.h"
using namespace std;

void GameManager::startGame() {
	int menuSelection = 0;
	while (menuSelection != 9) {
		menuSelection = showMenu();
		switch (menuSelection) {
		case 1:
			clearScreen();
			this->isGameRunning = true;
			GameConfig::setColorSupport(false); 
			this->LUser.resetBoard();
			this->LUser.createNewMovingBlock();
			this->RUser.resetBoard();
			this->RUser.createNewMovingBlock();
			this->LUser.resetScore();
			playGame();
			break;
		case 2:
			clearScreen();
			playGame();
			break;
		case 4: 
			clearScreen();
			this->isGameRunning = true;
			GameConfig::setColorSupport(true);
			this->LUser.resetBoard();
			this->LUser.createNewMovingBlock();
			this->RUser.resetBoard();
			this->RUser.createNewMovingBlock();
			this->LUser.resetScore();
			playGame();
			break;
		case 9:
			return;
		}

	}
}

int GameManager::showMenu() {
	while (true) {
		clearScreen();
		cout << "Please select one of the following options in order to continue:" << endl;
		cout << "(1) Start a new game - without colors" << endl;
		if (this->isGameRunning)
			cout << "(2) Continue a paused game" << endl;
		cout << "(4) Start a new game - with colors" << endl;
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl;

		char pressedChar = _getch();

		switch ((int)pressedChar) {
		case '1':
			clearScreen();
			cout << "A new game will be started in 3 seconds.." << endl;
			Sleep(3000);
			return 1;
		case '2':
			if (this->isGameRunning) {
				clearScreen();
				cout << "The game will be resumed in 3 seconds.." << endl;
				Sleep(3000);
				return 2;
			}
			else {
				cout << "Invalid selection. Please try again." << endl;
				Sleep(400);
				break;
			}
		case '4': 
			clearScreen();
			cout << "A new game with colors will be started in 3 seconds.." << endl;
			Sleep(3000);
			return 4;
		case '8':
			clearScreen();
			showInstructions();
			Sleep(750);
			break;
		case '9':
			clearScreen();
			cout << "The game will exit in 3 seconds.." << endl;
			Sleep(3000);
			return 9;
		default:
			cout << "Invalid selection. Please try again." << endl;
			Sleep(400);
			break;
		}
	}
}


void GameManager::playGame() {
	drawBoards();
	bool leftBlockMoved = false;
	bool rightBlockMoved = false;

	//rand((time(nullptr)));
	Sleep(1000);

	while (this->isGameRunning)
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
				return;
			}
		}

		leftBlockMoved = this->LUser.moveMovingBlock(GameConfig::eKeys::DROPP1);
		rightBlockMoved = this->RUser.moveMovingBlock(GameConfig::eKeys::DROPP2);

		// Checks if a block couldn't move, make it static and create new block
		if (!leftBlockMoved && !rightBlockMoved) {
			if (this->LUser.getMovingBlock().getMovedAmount() == 0 || this->RUser.getMovingBlock().getMovedAmount() == 0) {
				updateScoreTable();
				gotoxy(0, GameConfig::BOARD_HEIGHT + 5);
				if(this->LUser.getScore() > this->RUser.getScore())
					cout << "Left player Won due to Higher score !!";
				else if(this->RUser.getScore() > this->LUser.getScore())
					cout << "Right player Won due to Higher score !!";
				else
					cout << "This is a TIE !!";
				this->isGameRunning = false;
				Sleep(3000);
				return;
			}
		}
		if (!leftBlockMoved) {
			if (this->LUser.getMovingBlock().getMovedAmount() == 0) {
				gotoxy(0, GameConfig::BOARD_HEIGHT + 5);
				cout << "Right Player Won !";
				this->isGameRunning = false;
				Sleep(3000);
				return;
			}
			this->LUser.updateBoardAndAssignGenerateNewBlock();
			updateScoreTable();
		}
		if (!rightBlockMoved) {
			if (this->RUser.getMovingBlock().getMovedAmount() == 0) {
				gotoxy(0, GameConfig::BOARD_HEIGHT + 5);
				cout << "Left Player Won !";
				this->isGameRunning = false;
				Sleep(3000);
				return;
			}
			this->RUser.updateBoardAndAssignGenerateNewBlock();
			updateScoreTable();
		}
		Sleep(800);
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


void GameManager::drawBoards() {
	this->LUser.getBoard().drawBoard('L');
	this->RUser.getBoard().drawBoard('R');
	this->LUser.getMovingBlock().drawBlock();
	this->RUser.getMovingBlock().drawBlock();
	drawScore();
}

void GameManager::drawScore()
{
	//Players score
	gotoxy(GameConfig::BOARD_WIDTH + 5, GameConfig::MIN_Y - 1);
	cout << "P1";
	gotoxy(GameConfig::BOARD_WIDTH + 5, GameConfig::MIN_Y);
	cout << "Score:";
	gotoxy(GameConfig::BOARD_WIDTH + 12, GameConfig::MIN_Y - 1);
	cout << "P2";
	gotoxy(GameConfig::BOARD_WIDTH + 12, GameConfig::MIN_Y);
	cout << "Score:";
	updateScoreTable();
}

void GameManager::updateScoreTable() {
	gotoxy(GameConfig::BOARD_WIDTH + 5, GameConfig::MIN_Y + 1);
	cout << this->LUser.getScore();
	gotoxy(GameConfig::BOARD_WIDTH + 12, GameConfig::MIN_Y + 1);
	cout << this->RUser.getScore();
}
