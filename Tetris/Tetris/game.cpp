// Implementation file for the GameManager class.

#include "game.h"
#include <iostream>
#include <windows.h>
#include <conio.h> 
#include "block.h"
#include "user.h"
#include "general.h"
#include "gameConfig.h"
using namespace std;

// Method to set up a new game
void GameManager::setupNewGame(bool useColors) {
	clearScreen();
	this->isGameRunning = true;
	GameConfig::setColorSupport(useColors);
	this->LUser.resetBoard();
	this->LUser.createNewMovingBlock();
	this->RUser.resetBoard();
	this->RUser.createNewMovingBlock();
	this->LUser.resetScore();
}

// Start the game and handle menu selections
void GameManager::startGame() {
	int menuSelection = 0;
	while (menuSelection != 9) {
		menuSelection = showMenu();
		switch (menuSelection) {
		case 1:
			setupNewGame(false);  // Start a new game without colors
			playGame();
			break;
		case 2:
			clearScreen();
			playGame();  // Continue a paused game
			break;
		case 4:
			setupNewGame(true);  // Start a new game with colors
			playGame();
			break;
		case 9:
			return;
		}
	}
}

// Display the main menu and return the user's selection
int GameManager::showMenu() {
	while (true) {
		clearScreen();
		cout << "Please select one of the following options in order to continue:" << endl;
		cout << "(1) Start a new game - without colors" << endl;

		// Display option to continue a paused game only if the game is already running
		if (this->isGameRunning)
			cout << "(2) Continue a paused game" << endl;

		cout << "(4) Start a new game - with colors" << endl;
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl << endl;

		// Reminder for playing
		cout << "Please switch your keyboard to English to play the game." << endl;
		cout << "If needed, press Alt + Shift simultaneously to change the language." << endl << endl;

		char pressedChar = _getch();

		switch ((int)pressedChar) {
		case '1':
			clearScreen();
			cout << "A new game will start in 3 seconds.." << endl;
			Sleep(3000);
			return 1;
		case '2':
			if (this->isGameRunning) {
				clearScreen();
				cout << "The game will resume in 3 seconds.." << endl;
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
			cout << "A new game with colors will start in 3 seconds.." << endl;
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

// Display game instructions
void GameManager::showInstructions() {
	// Brief explanation of Tetris
	cout << "Hello and welcome to Lidor & Bar Tetris game!" << endl;
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

	// Reminder for playing
	cout << "Switch your keyboard to English to play." << endl;
	cout << "If needed, press Alt + Shift simultaneously to change the language." << endl << endl;

	// Instruction how to return to main menu
	cout << "Press ESC key to return." << endl << endl;

	// Wait for user input to return to the main menu
	while (true) {
		if (_kbhit()) {
			if ((GameConfig::eKeys)_getch() == GameConfig::eKeys::ESC)
				return;
			else
			{
				cout << "Invalid selection. Please try again." << endl;
				Sleep(500);
			}
		}
		Sleep(10);
	}
}

// Play the main game loop
void GameManager::playGame() {
	drawBoards();
	bool leftBlockMoved = false;
	bool rightBlockMoved = false;

	while (this->isGameRunning) {
		if (_kbhit()) {
			char pressedChar = _getch();
			pressedChar = tolower(pressedChar);
			leftBlockMoved = false;
			rightBlockMoved = false;

			switch ((GameConfig::eKeys)pressedChar) {

				// Left player controls
			case GameConfig::eKeys::LEFTP1:
				this->LUser.moveMovingBlock(GameConfig::eKeys::LEFTP1);
				break;
			case GameConfig::eKeys::RIGHTP1:
				this->LUser.moveMovingBlock(GameConfig::eKeys::RIGHTP1);
				break;
			case GameConfig::eKeys::DROPP1:
				this->LUser.moveMovingBlock(GameConfig::eKeys::DROPP1);
				break;
			case GameConfig::eKeys::ROTATE_CLOCKP1:
				this->LUser.rotateMovingBlock();
				break;
			case GameConfig::eKeys::ROTATE_COUNTERP1:
				this->LUser.rotateMovingBlock(false);
				break;

				// Right player controls
			case GameConfig::eKeys::LEFTP2:
				this->RUser.moveMovingBlock(GameConfig::eKeys::LEFTP2);
				break;
			case GameConfig::eKeys::RIGHTP2:
				this->RUser.moveMovingBlock(GameConfig::eKeys::RIGHTP2);
				break;
			case GameConfig::eKeys::DROPP2:
				this->RUser.moveMovingBlock(GameConfig::eKeys::DROPP2);
				break;
			case GameConfig::eKeys::ROTATE_CLOCKP2:
				this->RUser.rotateMovingBlock();
				break;
			case GameConfig::eKeys::ROTATE_COUNTERP2:
				this->RUser.rotateMovingBlock(false);
				break;

				// User paused
			case GameConfig::eKeys::ESC:
				gotoxy(0, GameConfig::BOARD_HEIGHT + 5);
				cout << "The game has been paused, you will be moved to the main menu in 5 seconds." << endl;
				cout << "Please note that you can resume the game by pressing (2) in the main menu." << endl;
				Sleep(5000);
				return;
			}
		}

		// Move the blocks down and check if they couldn't move
		leftBlockMoved = this->LUser.moveMovingBlock(GameConfig::eKeys::DROPP1);
		rightBlockMoved = this->RUser.moveMovingBlock(GameConfig::eKeys::DROPP2);

		// Check if neither leftBlock nor rightBlock could move
		if (!leftBlockMoved && !rightBlockMoved) {
			// Check if either block reached the top, signaling the end of the game
			if (this->LUser.getMovingBlock().getMovedAmount() == 0 || this->RUser.getMovingBlock().getMovedAmount() == 0) {
				updateScoreTable();
				gotoxy(0, GameConfig::BOARD_HEIGHT + 5);
				handleBlockNotMoved(true);
			}
		}

		// Check if leftBlock couldn't move
		if (!leftBlockMoved) {
			// Check if the leftBlock reached the top
			if (this->LUser.getMovingBlock().getMovedAmount() == 0) {
				gotoxy(0, GameConfig::BOARD_HEIGHT + 5);
				cout << "Right Player Won !" << endl << endl;
				handleBlockNotMoved(false);
			}

			// Update the leftBlock's board and generate a new block
			this->LUser.updateBoardAndGenerateNewBlock();
			updateScoreTable();
		}

		// Check if rightBlock couldn't move
		if (!rightBlockMoved) {
			// Check if the rightBlock reached the top
			if (this->RUser.getMovingBlock().getMovedAmount() == 0) {
				gotoxy(0, GameConfig::BOARD_HEIGHT + 5);
				cout << "Left Player Won !" << endl << endl;
				handleBlockNotMoved(false);
			}

			// Update the rightBlock's board and generate a new block
			this->RUser.updateBoardAndGenerateNewBlock();
			updateScoreTable();
		}
		Sleep(800);
	}
}

// Method to handle the case when a player wins or the game is tied
void GameManager::handleBlockNotMoved(bool isHighScore) {
	// Determine the winner or tie based on scores
	if (isHighScore) {
		if (this->LUser.getScore() > this->RUser.getScore())
			cout << "Left player Won due to Higher score !!";
		else if (this->RUser.getScore() > this->LUser.getScore())
			cout << "Right player Won due to Higher score !!";
		else
			cout << "This is a TIE !!";
	}

	cout << "Press any key to return to main menu" << endl;

	// Wait for user input
	while (true) {
		if (_kbhit())
			break;
		Sleep(10);
	}

	this->isGameRunning = false;
	Sleep(3000);
}

// Draw the game boards and moving blocks
void GameManager::drawBoards() {
	this->LUser.getBoard().drawBoard('L');
	this->RUser.getBoard().drawBoard('R');
	this->LUser.getMovingBlock().drawBlock();
	this->RUser.getMovingBlock().drawBlock();
	drawScore();
}

// Draw the scores for both players
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

// Update the score table on the screen
void GameManager::updateScoreTable() {
	gotoxy(GameConfig::BOARD_WIDTH + 5, GameConfig::MIN_Y + 1);
	cout << this->LUser.getScore();
	gotoxy(GameConfig::BOARD_WIDTH + 12, GameConfig::MIN_Y + 1);
	cout << this->RUser.getScore();
}