// Header file for the GameManager class.

#ifndef __GAME_H
#define __GAME_H

#include "user.h"

class GameManager 
{
	User LUser;
	User RUser;
	bool isGameRunning;
	bool isGameSupportColors;
    int option;

public:
    // Constructor
    GameManager() : LUser('L'), RUser('R'), isGameRunning(false), isGameSupportColors(false), option((int)GameConfig::eKeys::HumanVsHuman) {};

    // Method to set up a new game
    void setupNewGame(bool useColors);

    // Start the game and handle menu selections
    void startGame();

    // Display the main menu and return the user's selection
    int showMenu();

    // Display game instructions
    void showInstructions();

    // Play the main game loop
    void playGame();

    // Method to handle the case when a player wins or the game is tied
    void handleBlockNotMoved(bool isHighScore);

    // Draw the game boards and moving blocks
    void drawBoards();

    // Draw the scores for both players
    void drawScore();

    // Update the score table on the screen
    void updateScoreTable();

    //Check if the user provided reached the top part of the board and handle as the result
    void checkUserReachedTop(User& user);
};

#endif