// Implementation file for the GameManager class.

#include "game.h"
#include <iostream>
#include <windows.h>
#include <conio.h> 
#include "block.h"
#include "user.h"
#include "general.h"
#include "gameConfig.h"
#include "humanUser.h"
#include "computerUser.h"
#include <typeinfo>

// Method to set up a new game
void GameManager::setupNewGame(bool useColors) {
	clearScreen();
	this->isGameRunning = true;
	GameConfig::setColorSupport(useColors);
	setUpUsers();
}

// Setup the relevant users
void GameManager::setUpUsers() {
	clearScreen();

	switch ((GameConfig::eKeys)this->option) {
	case GameConfig::eKeys::HumanVsHuman:
		this->LUser = new HumanUser('L');
		this->RUser = new HumanUser('R');
		break;
	case GameConfig::eKeys::HumanVsComputer:
		this->LUser = new HumanUser('L');
		this->RUser = new ComputerUser('R', computerLevel('R'));
		break;
	case GameConfig::eKeys::ComputerVsComputer:
		this->LUser = new ComputerUser('L', computerLevel('L'));
		this->RUser = new ComputerUser('R', computerLevel('R'));
		break;
	}
}

// Start the game and handle menu selections
void GameManager::startGame() {
	int menuSelection = 0;
	while (menuSelection != 9) {
		menuSelection = showMenu();
		switch ((GameConfig::eKeys)menuSelection) {
		// Start a new game without colors
		case GameConfig::eKeys::HumanVsHuman:
		case GameConfig::eKeys::HumanVsComputer:
		case GameConfig::eKeys::ComputerVsComputer:
			this->option = menuSelection % 4;
			setupNewGame(false);  
			playGame();
			break;

		// Continue a paused game
		case GameConfig::eKeys::ContinuePausedGame:
			clearScreen();
			playGame();
			break;

		// Start a new game with colors
		case GameConfig::eKeys::HumanVsHumanColors:
		case GameConfig::eKeys::HumanVsComputerColors:
		case GameConfig::eKeys::ComputerVsComputerColors:
			this->option = menuSelection % 4;
			setupNewGame(true);  
			playGame();
			break;

		// Quit the game
		case GameConfig::eKeys::Quit:
			return;
		}
	}
}

// Display the main menu and return the user's selection
int GameManager::showMenu() {
	while (true) {
		clearScreen();
		std::cout << "Please select one of the following options in order to continue:" << std::endl << std::endl;
		std::cout << "Game without colors:" << std::endl;
		std::cout << "(1) Start a new game - Human vs Human" << std::endl;
		std::cout << "(2) Start a new game - Human vs Computer" << std::endl;
		std::cout << "(3) Start a new game - Computer vs Computer" << std::endl << std::endl;

		// Display option to continue a paused game only if the game is already running
		if (this->isGameRunning)
			std::cout << "(4) Continue a paused game" << std::endl << std::endl;

		std::cout << "Game with colors:" << std::endl;
		std::cout << "(5) Start a new colored game - Human vs Human" << std::endl;
		std::cout << "(6) Start a new colored game - Human vs Computer" << std::endl;
		std::cout << "(7) Start a new colored game - Computer vs Computer" << std::endl << std::endl;

		std::cout << "(8) Present instructions and keys" << std::endl;
		std::cout << "(9) EXIT" << std::endl << std::endl;

		// Reminder for playing
		std::cout << "Please switch your keyboard to English to play the game." << std::endl;
		std::cout << "If needed, press Alt + Shift simultaneously to change the language." << std::endl << std::endl;

		int selectedOption = _getch() - '0';
		
		switch ((GameConfig::eKeys)selectedOption) {
		case GameConfig::eKeys::HumanVsHuman:
		case GameConfig::eKeys::HumanVsComputer:
		case GameConfig::eKeys::ComputerVsComputer:
			clearScreen();
			std::cout << "A new game will start in 3 seconds.." << std::endl;
			Sleep(3000);
			return selectedOption;
		case GameConfig::eKeys::ContinuePausedGame:
			if (this->isGameRunning) {
				clearScreen();
				std::cout << "The game will resume in 3 seconds.." << std::endl;
				Sleep(3000);
				return selectedOption;
			}
			else {
				std::cout << "Invalid selection. Please try again." << std::endl;
				Sleep(400);
				break;
			}
		case GameConfig::eKeys::HumanVsHumanColors:
		case GameConfig::eKeys::HumanVsComputerColors:
		case GameConfig::eKeys::ComputerVsComputerColors:
			clearScreen();
			std::cout << "A new colored game will start in 3 seconds.." << std::endl;
			Sleep(3000);
			return selectedOption;
		case GameConfig::eKeys::Instructions:
			clearScreen();
			showInstructions();
			Sleep(750);
			break;
		case GameConfig::eKeys::Quit:
			clearScreen();
			std::cout << "The game will exit in 3 seconds.." << std::endl;
			Sleep(3000);
			return 9;
		default:
			std::cout << "Invalid selection. Please try again." << std::endl;
			Sleep(400);
			break;
		}
	}
}

// Display game instructions
void GameManager::showInstructions() {
	// Brief explanation of Tetris
	std::cout << "Hello and welcome to Lidor & Bar Tetris game!" << std::endl;
	std::cout << "Tetris is a puzzle game where you must fit falling blocks into a line at the bottom of the playing board." << std::endl;
	std::cout << "Completing a line clears it and earns points, the game ends when the blocks reach the top of the board." << std::endl << std::endl;

	// Instructions for the game controls
	std::cout << "Here are the controls for the game:" << std::endl << std::endl;

	// Instructions for the left player
	std::cout << "Left Player Human Controls:" << std::endl;
	std::cout << "Move Left: Press 'a' or 'A'" << std::endl;
	std::cout << "Move Right: Press 'd' or 'D'" << std::endl;
	std::cout << "Rotate Clockwise: Press 's' or 'S'" << std::endl;
	std::cout << "Rotate Counterclockwise: Press 'w' or 'W'" << std::endl;
	std::cout << "Drop: Press 'x' or 'X'" << std::endl << std::endl;

	// Instructions for the right player
	std::cout << "Right Player Human Controls:" << std::endl;
	std::cout << "Move Left: Press 'j' or 'J'" << std::endl;
	std::cout << "Move Right: Press 'l' or 'L'" << std::endl;
	std::cout << "Rotate Clockwise: Press 'k' or 'K'" << std::endl;
	std::cout << "Rotate Counterclockwise: Press 'i' or 'I'" << std::endl;
	std::cout << "Drop: Press 'm' or 'M'" << std::endl << std::endl;

	// Instructions for the bomb
	std::cout << "Bomb Instructions:" << std::endl;
	std::cout << "Bombs can randomly appear during the game with a 5% chance." << std::endl;
	std::cout << "If a bomb reaches the bottom of the board, it will explode and destroy everything in a 9x9 area." << std::endl << std::endl;

	// Reminder for playing
	std::cout << "Switch your keyboard to English to play." << std::endl;
	std::cout << "If needed, press Alt + Shift simultaneously to change the language." << std::endl << std::endl;

	// Instruction how to return to main menu
	std::cout << "Press ESC key to return." << std::endl << std::endl;

	// Wait for user input to return to the main menu
	while (true) {
		if (_kbhit()) {
			if ((GameConfig::eKeys)_getch() == GameConfig::eKeys::ESC)
				return;
			else
			{
				std::cout << "Invalid selection. Please try again." << std::endl;
				Sleep(500);
			}
		}
		Sleep(10);
	}
}

// Play the main game loop
void GameManager::playGame() {
	drawBoards();
	bool leftBlockMoved = false, rightBlockMoved = false;
	while (this->isGameRunning) {
		while (_kbhit()) {
			char pressedChar = _getch();
			pressedChar = tolower(pressedChar);
			leftBlockMoved = rightBlockMoved = false;
			if ((GameConfig::eKeys)pressedChar == GameConfig::eKeys::ESC) {
				gotoxy(0, GameConfig::BOARD_HEIGHT + 5);
				std::cout << "The game has been paused, you will be moved to the main menu in 5 seconds." << std::endl;
				std::cout << "Please note that you can resume the game by pressing (2) in the main menu." << std::endl;
				Sleep(5000);
				return;
			}
			// Human user
			if (!LUser->getIfMoved()) 
				LUser->handleMovement((GameConfig::eKeys)pressedChar);
			if (!RUser->getIfMoved())
				RUser->handleMovement((GameConfig::eKeys)pressedChar);
		}
		// Allows the player to make another move
		LUser->setMoved(false);
		RUser->setMoved(false);

		// Computer user
		LUser->handleMovement();
		RUser->handleMovement();

		// Move the blocks down and check if they couldn't move
		leftBlockMoved = this->LUser->moveMovingBlock(GameConfig::eKeys::DROPP1);
		rightBlockMoved = this->RUser->moveMovingBlock(GameConfig::eKeys::DROPP2);

		// Check if neither leftBlock nor rightBlock could move
		if (!leftBlockMoved && !rightBlockMoved) {
			// Check if either block reached the top, signaling the end of the game
			if (this->LUser->getMovingBlock().getMovedAmount() == 0 || this->RUser->getMovingBlock().getMovedAmount() == 0) {
				updateScoreTable();
				gotoxy(0, GameConfig::BOARD_HEIGHT + 5);
				handleBlockNotMoved(true);
			}
		}

		// Check if leftBlock couldn't move
		if (!leftBlockMoved) 
			checkUserReachedTop(*this->LUser);

		// Check if rightBlock couldn't move
		if (!rightBlockMoved) 
			checkUserReachedTop(*this->RUser);

		// Game speed
		Sleep(100);
	}
}

//Check if the user provided reached the top part of the board and handle as the result
void GameManager::checkUserReachedTop (User& user) {
	// Check if the users Block reached the top
	if (user.getMovingBlock().getMovedAmount() == 0) {
		gotoxy(0, GameConfig::BOARD_HEIGHT + 5);
		std::cout << ((user.getSide() == 'L') ? "Right" : "Left") << " Player Won !" << std::endl << std::endl;
		handleBlockNotMoved(false);
	}
	// Update the users board and generate a new block
	user.updateBoardAndGenerateNewBlock();
	updateScoreTable();
}


// Method to handle the case when a player wins or the game is tied
void GameManager::handleBlockNotMoved(bool isHighScore) {
	// Determine the winner or tie based on scores
	if (isHighScore) {
		if (this->LUser->getScore() > this->RUser->getScore())
			std::cout << "Left player Won due to Higher score !!" << std::endl;
		else if (this->RUser->getScore() > this->LUser->getScore())
			std::cout << "Right player Won due to Higher score !!" << std::endl;
		else
			std::cout << "This is a TIE !!" << std::endl;
	}

	std::cout << "Press any key to return to main menu" << std::endl;

	// Wait for user input
	while (true) {
		if (_kbhit())
			break;
		Sleep(10);
	}

	this->isGameRunning = false;
}

// Draw the game boards and moving blocks
void GameManager::drawBoards() {
	this->LUser->getBoard().drawBoard('L');
	this->RUser->getBoard().drawBoard('R');
	this->LUser->getMovingBlock().drawBlock();
	this->RUser->getMovingBlock().drawBlock();
	drawScore();
}

// Draw the scores for both players
void GameManager::drawScore()
{
	//Players score
	gotoxy(GameConfig::BOARD_WIDTH + 5, GameConfig::MIN_Y - 1);
	std::cout << "P1";
	gotoxy(GameConfig::BOARD_WIDTH + 5, GameConfig::MIN_Y);
	std::cout << "Score:";
	gotoxy(GameConfig::BOARD_WIDTH + 12, GameConfig::MIN_Y - 1);
	std::cout << "P2";
	gotoxy(GameConfig::BOARD_WIDTH + 12, GameConfig::MIN_Y);
	std::cout << "Score:";
	updateScoreTable();
}

// Update the score table on the screen
void GameManager::updateScoreTable() {
	gotoxy(GameConfig::BOARD_WIDTH + 5, GameConfig::MIN_Y + 1);
	std::cout << this->LUser->getScore();
	gotoxy(GameConfig::BOARD_WIDTH + 12, GameConfig::MIN_Y + 1);
	std::cout << this->RUser->getScore();
}

// Ask the user for the relevant computer level
int GameManager::computerLevel(char side) {
	int choice = 1;
	bool isChosen = false;
	while (!isChosen) {
		clearScreen();
		std::cout << "Please select the requested level for the ";
		if (side == 'L') {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[1]);
			std::cout << "Left side." << std::endl << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[2]);
			std::cout << "Right side." << std::endl << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
		}

		std::cout << "(a) Best level" << std::endl;
		std::cout << "(b) Good level" << std::endl;
		std::cout << "(c) Novice level" << std::endl << std::endl;

		char selectedOption = _getch();
		switch (selectedOption) {
		case 'a':
			isChosen = true;
			break;
		case 'b':
			isChosen = true;
			choice = 2;
			break;
		case 'c':
			isChosen = true;
			choice = 3;
			break;
		default:
			std::cout << "Invalid selection. Please try again." << std::endl;
			Sleep(400);
			break;
		}
	}
	if (side == 'R')
	{
		clearScreen();
		std::cout << "A new game will start in 3 seconds.." << std::endl;
		Sleep(3000);
		clearScreen();
	}
	else {
		clearScreen();
		Sleep(200);
	}
	return choice;
}

// Destructor
GameManager::~GameManager() {
	if (LUser != nullptr) {
		delete LUser;
		LUser = nullptr;
	}
	if (RUser != nullptr) {
		delete RUser;
		RUser = nullptr;
	}
}
