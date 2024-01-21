// Implementation file for the Board class.

#include "board.h"
#include "general.h"
#include <iostream>
#include <Windows.h>

using namespace std;

// Constructor
Board::Board(char side) {
	clearBoard();
	this->side = side;
}

// Clears the entire game board
void Board::clearBoard() {
	for (int row = 0; row < GameConfig::BOARD_HEIGHT; row++) {
		for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
			this->board[col][row].setSymbol(' ');
		}
	}
}

// Draws the game board, including borders and current block positions
void Board::drawBoard(char side) {
	int startX = 0, startY = 0;
	if (side == 'R')
		startX = GameConfig::RIVAL_POS;

	// Print the top border
	gotoxy(startX, startY++);
	for (int i = 0; i < GameConfig::BOARD_WIDTH + 2; i++) {
		cout << "-";
	}

	// Print the board content
	gotoxy(startX, startY);
	for (int row = 0; row <= GameConfig::BOARD_HEIGHT - 1; row++) {
		cout << "|";  // Print the leftmost vertical bar
		for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
			char symbol = this->board[col][row].getSymbol();
			if (symbol == '#')
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->board[col][row].getColor());
			cout << symbol;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
		}
		cout << '|';  // Print the rightmost vertical bar for the last column
		gotoxy(startX, startY + row + 1);
	}

	// Print the bottom border
	for (int i = 0; i < GameConfig::BOARD_WIDTH + 2; i++) {
		cout << "-";
	}

	this->side = side;
}

// Updates the game board with the current block's points
void Board::updateBoardWithPoints(Point* points) {
	int xOffset = this->side == 'L' ? 1 : GameConfig::RIVAL_POS + 1;
	int row, col;
	for (int i = 0; i < 4; i++) {
		row = points[i].getX() - xOffset;
		col = points[i].getY() - 1;
		this->board[row][col].setSymbol(points[i].getSymbol());
		this->board[row][col].setColor(points[i].getColor());
	}
}

// Validates and clears full rows, updating the board and returning the score
int Board::validateBoard() {
	int scoreReceived = 0;
	int multiplier = 1;
	bool redrawRequired = false;

	for (int i = GameConfig::BOARD_HEIGHT - 1; i >= 0; i--) {
		if (isAllRowFull(i)) {
			bombRowAndFixBoard(i);
			redrawRequired = true;
			scoreReceived += (5 * multiplier);
			multiplier *= 2;
		}
	}

	if (redrawRequired)
		drawBoard(this->side);

	return scoreReceived;
}

// Checks if a given row is completely filled with blocks
bool Board::isAllRowFull(int row) const {
	for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
		if (this->board[col][row].getSymbol() == ' ')
			return false;
	}
	return true;
}

// Clears a filled row and shifts the above rows down
void Board::bombRowAndFixBoard(int row) {
	for (; row > 0; row--) {
		for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
			this->board[col][row] = this->board[col][row - 1];
		}
	}
	for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
		this->board[col][0].setSymbol(' ');
	}
}